#include "utils.h"
#include "queue.h"
#include "bme280.h"
#include "bh1750.h"
#include "module.h"
#include "sensors.h"
#include "digital_io.h"

#include <string.h>

#define SENSOR_MAX_NAME_LENGTH		32
#define MAX_SENSOR_COUNT		128

typedef enum constraint_res {
	CONSTRAINT_OK = 0,
	CONSTRAINT_VIOLATED,
} constraint_res_t;

/**
 * Sensor management
 */
static sensor_t *g_sensors[MAX_SENSOR_COUNT] = {NULL};

static SLIST_HEAD(,sensor_handler) g_sensors_handler_list = SLIST_HEAD_INITIALIZER(g_sensors_handler_list);
static SLIST_HEAD(,sensor_watcher) g_sensors_watcher_list = SLIST_HEAD_INITIALIZER(g_sensors_watcher_list);
static SLIST_HEAD(,sensor_constraint) g_sensors_constraint_list = SLIST_HEAD_INITIALIZER(g_sensors_constraint_list);

static const char *constraint_type_to_str[] = {
	[SENSORS_CST_TYPE_NOR] = "NOR",
};

static const char *sensor_type_to_str[] = {
	[SENSORS_TYPE_SWITCH] = "switch",
	[SENSORS_TYPE_HUMIDITY] = "humidity",
	[SENSORS_TYPE_TEMP] = "temperature",
	[SENSORS_TYPE_PRESSURE] = "pressure",
	[SENSORS_TYPE_LIGHT] = "light",
};

int
sensors_register_handler(sensor_handler_t *sensor_handler)
{
	SLIST_INSERT_HEAD(&g_sensors_handler_list, sensor_handler, link);
	return 0;
}

int
sensors_register_watcher(sensor_watcher_t *sensor_watcher)
{
	SLIST_INSERT_HEAD(&g_sensors_watcher_list, sensor_watcher, link);
	return 0;
}

sensor_t *
sensors_get_by_id(int id)
{
	if (id > MAX_SENSOR_COUNT)
		return NULL;

	return g_sensors[id];	
};

static int
sensors_sensor_created(sensor_t* s)
{
	struct sensor_watcher *w;
	
	SLIST_FOREACH(w, &g_sensors_watcher_list, link) {
		if (w->sensor_created) {
			w->sensor_created(s);
		}
	}

	return 0;
}

sensor_t *
sensor_create(sensors_type_t type, const char *name, unsigned char id, const sensors_ops_t *ops, void *data)
{
	sensor_t *s;

	PANIC_ON(id >= MAX_SENSOR_COUNT, "Id is too big");
	PANIC_ON(g_sensors[id] != NULL, "Duplicated sensors id");

	s = calloc(1, sizeof(*s));
	if (!s)
		return NULL;

	SLIST_INIT(&s->constraints);
	strncpy(s->name, name, SENSOR_MAX_NAME_LENGTH);
	s->id = id;
	s->type = type;
	s->ops = ops;
	s->data = data;
	g_sensors[id] = s;


	sensor_get_value(s, &s->val);
	dbg_log("Sensor %s initial value: %d\n", s->name, s->val.val_i);
	sensors_sensor_created(s);

	return s;
}


static void
sensors_main_loop()
{
	struct sensor_handler *handler;
	
	SLIST_FOREACH(handler, &g_sensors_handler_list, link) {
		if (handler->poll)
			handler->poll();
	}
}

int
sensors_sensor_update(sensor_t* s, sensor_value_t new_value)
{
	struct sensor_watcher *w;
	
	SLIST_FOREACH(w, &g_sensors_watcher_list, link) {
		if (w->sensor_updated) {
			w->sensor_updated(s, new_value);
		}
	}

	return 0;
}

static constraint_res_t
sensor_check_constraint(sensor_t *s, sensor_value_t new_value)
{
	sensor_constraint_ptr_t *cst_ptr;
	sensor_constraint_t *cst;
	sensor_t *other;
	
	SLIST_FOREACH(cst_ptr, &s->constraints, link) {
		cst = cst_ptr->cst;
		switch (cst->type) {
			case SENSORS_CST_TYPE_NOR:
				/* Determine other sensor */
				other = (s == cst->data.nor.s1) ? cst->data.nor.s2 : cst->data.nor.s1;

				dbg_log("Checking nor constraint for sensor %s val %d and %s val %d\n",
						sensor_get_name(s),
						new_value.val_i,
						sensor_get_name(other),
						other->val.val_i);

				if (new_value.val_i == 1 && other->val.val_i == 1) {
					return CONSTRAINT_VIOLATED;
				}

			break;
		}
	}
	return CONSTRAINT_OK;
}

void
sensor_set_value(sensor_t *s, sensor_value_t value)
{
	if (sensor_check_constraint(s, value) == CONSTRAINT_VIOLATED) {
		dbg_log("Constraint violated\n");
		return;
	}

	/* Update value */
	s->val = value;

	if (s->ops->set)
		s->ops->set(s, s->data, value);
}

void
sensor_get_value(sensor_t *s, sensor_value_t *value)
{
	if (s->ops->req)
		s->ops->req(s, s->data, value);
}

static void
sensor_add_constraint(sensor_constraint_t *cst, sensor_t *s)
{
	sensor_constraint_ptr_t *cst_ptr = malloc(sizeof(sensor_constraint_ptr_t));
	PANIC_ON(!cst_ptr, "Failed to alloc constraint ptr");

	cst_ptr->cst = cst;
	SLIST_INSERT_HEAD(&s->constraints, cst_ptr, link);
}

static int
constraint_json_parse_one(json_value* section)
{
	int length, i;
	json_value *value;
	const char *name;
	sensor_constraint_t *cst;

	cst = calloc(1, sizeof(sensor_constraint_t));
	PANIC_ON(!cst, "Failed to alloc constraint");

        length = section->u.object.length;
        for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;

		if (strcmp(name, "type") == 0) {
			if (strcmp(value->u.string.ptr,"NOR"))
				cst->type = SENSORS_CST_TYPE_NOR;
		} else if (strcmp(name, "io1") == 0) {
			cst->data.nor.s1 = sensors_get_by_id(value->u.integer);
		} else if (strcmp(name, "io2") == 0) {
			cst->data.nor.s2 = sensors_get_by_id(value->u.integer);
		}
        }

	dbg_log("Adding constraint type %s, to sensor %s and %s\n", 
			constraint_type_to_str[cst->type],
			sensor_get_name(cst->data.nor.s1),
			sensor_get_name(cst->data.nor.s2));
	SLIST_INSERT_HEAD(&g_sensors_constraint_list, cst, link);
	sensor_add_constraint(cst, cst->data.nor.s1);
	sensor_add_constraint(cst, cst->data.nor.s2);

	return 0;
}


static int
constraint_json_parse(json_value* section)
{
	unsigned int i;

	if (section->type != json_array)
		return 1;

	dbg_log("Parsing contraints\n");
	for (i = 0; i < section->u.array.length; i++) {
		constraint_json_parse_one(section->u.array.values[i]);
	}

	return 0;
}


static int
sensors_json_parse(json_value* section)
{
	int length, i;
	json_value *value;
	const char *name;
	struct sensor_handler *handler;
	json_value *constraints = NULL;

        length = section->u.object.length;

        /* Parse each sensors and give them to the appropriate handler */
        for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;
		dbg_log("Adding section %s\n", name);

		if (strcmp(name, "constraints") == 0) {
			constraints = value;
			continue;
		}
	
		SLIST_FOREACH(handler, &g_sensors_handler_list, link) {
			if (strcmp(name, handler->name))
				continue;

			 handler->json_parse(value);
			 break;
		}
        }
        
        if (constraints != NULL)
		constraint_json_parse(constraints);

	return 0;
}


static void 
handle_sensors(int argc, char **argv)
{
	int i;
	sensor_t *sensor;
	
	for (i = 0; i < MAX_SENSOR_COUNT; i++) {
		if (g_sensors[i] == NULL)
			continue;
			
		sensor = g_sensors[i];

		dbg_puts("Sensor %d:\n - name: %s\n - type: %s\n",
			i,
			sensor->name,
			sensor_type_to_str[sensor->type]);
		
	}

}

static module_command_t sensor_commands[] = 
{
	{
		.name = "sensors",
		.help = "Display sensor list",
		.hdler = handle_sensors,
	}
};

/**
 * Module
 */
static const module_t sensors_module = {
	.name = "sensors",
	.main_loop = sensors_main_loop,
	.json_parse = sensors_json_parse,
	MODULE_COMMANDS(sensor_commands),
};

void
sensors_init()
{
	bme280_init();
	bh1750_init();
	digital_io_init();
	module_register(&sensors_module);
}
