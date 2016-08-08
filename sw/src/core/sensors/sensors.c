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

/**
 * Sensor management
 */
static sensor_t *g_sensors[MAX_SENSOR_COUNT] = {NULL};

static SLIST_HEAD(,sensor_handler) g_sensors_handler_list = SLIST_HEAD_INITIALIZER(g_sensors_handler_list);
static SLIST_HEAD(,sensor_watcher) g_sensors_watcher_list = SLIST_HEAD_INITIALIZER(g_sensors_watcher_list);

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

	strncpy(s->name, name, SENSOR_MAX_NAME_LENGTH);
	s->id = id;
	s->type = type;
	s->ops = ops;
	s->data = data;
	g_sensors[id] = s;

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


void
sensor_set_value(sensor_t *s, sensor_value_t value)
{
	if (s->ops->set)
		s->ops->set(s, s->data, value);
}

void
sensor_get_value(sensor_t *s, sensor_value_t *value)
{
	if (s->ops->req)
		s->ops->req(s, s->data, value);
}

static int
sensors_json_parse(json_value* section)
{
	int length, i;
	json_value *value;
	const char *name;
	struct sensor_handler *handler;

        length = section->u.object.length;

        /* Parse each sensors and give them to the appropriate handler */
        for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;
		debug_puts("Adding section %s\r\n", name);
	
		SLIST_FOREACH(handler, &g_sensors_handler_list, link) {
			if (strcmp(name, handler->name))
				continue;

			 handler->json_parse(value);
			 break;
		}
        }

	return 0;
}

/**
 * Module
 */
static const module_t sensors_module = {
	.name = "sensors",
	.main_loop = sensors_main_loop,
	.json_parse = sensors_json_parse,
};

void
sensors_init()
{
	bme280_init();
	bh1750_init();
	digital_io_init();
	module_register(&sensors_module);
}
