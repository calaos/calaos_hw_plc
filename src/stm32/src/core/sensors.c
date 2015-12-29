#include "json.h"
#include "utils.h"
#include "module.h"
#include "sensors.h"

#include <string.h>

#define SENSOR_MAX_NAME_LENGTH	32
#define MAX_SENSOR_COUNT	255

typedef struct sensors_ops {
	/**
	 * Function call in main loop
	 */
	void (* poll)(sensor_t *);
	/**
	 * Function call when set is received from controller
	 */
	void (* set)(sensor_t *, int subtype, const char *payload);
	/**
	 * Function call when request is received from controller
	 */
	void (* req)(sensor_t *, int subtype, const char *payload);
} sensors_ops_t;


/**
 * switch specific data
 */
typedef struct sensor_switch {
	en_gpio_t *io;
	int last_state;
} sensor_switch_t;

/**
 * Sensor struct
 */
typedef struct sensor {
	char name[SENSOR_MAX_NAME_LENGTH];
	unsigned int id;
        sensors_type_t type;
	const sensors_ops_t *ops;
        union {
		sensor_switch_t sw;
	} _;
} sensor_t;


/**
 * Sensor management
 */
static unsigned char g_max_sensor_id = 0;
static sensor_t *g_sensors[MAX_SENSOR_COUNT];

static const sensors_ops_t* g_sensor_ops[];

static const char *sensor_type_str[] = {
    [SENSORS_TYPE_SWITCH] = "switch",
};

static int
sensors_typestr_to_type(const char *name)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(sensor_type_str); i++) {
		if (strcmp(sensor_type_str[i], name) == 0) {
			return i;
		}
	}

	return -1;
}

sensors_type_t
sensor_get_type(sensor_t *s)
{
	return s->type;
}

char *
sensor_get_name(sensor_t *s)
{
	return s->name;
}

int
sensor_get_id(sensor_t *s)
{
	return s->id;
}

sensor_t *
sensors_get_by_id(int id)
{
	if (id >= g_max_sensor_id)
		return NULL;

	return g_sensors[id];	
};

static sensor_t *
sensor_create_sensor(sensors_type_t type, const char *name, unsigned char id)
{
	sensor_t *s;

	if (g_sensors[id] != NULL)
		return NULL;

	s = calloc(1, sizeof(*s));
	if (!s)
		return NULL;

	strncpy(s->name, name, SENSOR_MAX_NAME_LENGTH);
	s->id = id;
	s->type = type;
	s->ops = g_sensor_ops[type];
	g_sensors[id] = s;

	module_sensor_created(s);

	if (id > g_max_sensor_id)
		g_max_sensor_id = id;

	return s;
}


static int
sensors_json_parse_sensor(json_value* sensor)
{
	int length, i;
	const char *name;
	char s_name[SENSOR_MAX_NAME_LENGTH], s_gpio_name[SENSOR_MAX_NAME_LENGTH];
	unsigned char s_id = 0;
	int s_gpio_dir = GPIO_DIR_OUTPUT, s_reverse = 0, s_type = -1;
	gpio_debounce_t s_debounce = GPIO_DEBOUNCE_ENABLE;
	json_value *value;
	sensor_t *s;
	
        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			strcpy(s_name, value->u.string.ptr);
		} else if (strcmp(name, "gpio") == 0) {
			strcpy(s_gpio_name, value->u.string.ptr);
		} else if (strcmp(name, "direction") == 0) {
			if (strcmp(value->u.string.ptr, "input") == 0)
				s_gpio_dir = GPIO_DIR_INPUT;
		} else if (strcmp(name, "type") == 0) {
			s_type = sensors_typestr_to_type(value->u.string.ptr);
		} else if (strcmp(name, "reverse") == 0) {
			s_reverse = value->u.boolean;
		} else if (strcmp(name, "id") == 0) {
			s_id = value->u.integer;
		} else if (strcmp(name, "debounce") == 0) {
			s_debounce = value->u.boolean;
		}
        }

	/* TODO: Check parameters */
	s = sensor_create_sensor(s_type, s_name, s_id);
	/* TODO: per type parser */
	s->_.sw.io = en_gpio_setup(s_gpio_name, s_reverse, s_gpio_dir, s_debounce);

	return 0;
}


static int
sensors_json_parse(json_value* value)
{
        unsigned int length, i, j;
	json_value *entry;

	if (value == NULL || value->type != json_object) {
                return -1;
        }
     
        length = value->u.object.length;
        for (i = 0; i < length; i++) {
		/* We only care about sensor section*/
		if (strcmp(value->u.object.values[i].name, "sensors") == 0) {
			entry = value->u.object.values[i].value;
			for (j = 0; j < entry->u.array.length; j++) {
				sensors_json_parse_sensor(entry->u.array.values[j]);
			}

			return 0;
		}
        }

        return -1;
}

static void sensors_main_loop()
{
	unsigned int i;

	for (i = 0; i < g_max_sensor_id; i++) {
		if (g_sensors[i] == NULL)
			continue;

		sensor_t *sensor = g_sensors[i];
		if (sensor->ops->poll)
			sensor->ops->poll(sensor);
	}
}


/**
 *  Switch
 */
static void
switch_poll(sensor_t * sensor)
{
	sensor_switch_t *sw = &sensor->_.sw;
	int state = en_gpio_read(sw->io);

	if (state != sw->last_state) {
		sw->last_state = state;
		//~ mysensors_update_value_int(sensor, V_STATUS, state);
	}
}

static void
switch_set(sensor_t * sensor, __unused__ int subtype, const char *payload)
{
	sensor_switch_t *sw = &sensor->_.sw;
	int state;
	if (en_gpio_get_dir(sw->io) != GPIO_DIR_OUTPUT)
		return;
	
	state = atoi(payload);
	en_gpio_write(sw->io, state);
}

sensors_ops_t switch_ops =
{
	.poll = switch_poll,
	.set = switch_set,
	.req = NULL,
};

static const sensors_ops_t* g_sensor_ops[] = {
    [SENSORS_TYPE_SWITCH] = &switch_ops,
};

/**
 * Module
 */
const module_t sensors_module = {
	.name = "sensors",
	.main_loop = sensors_main_loop,
	.json_parse = sensors_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};

void
sensors_init()
{
	module_register(&sensors_module);
}
