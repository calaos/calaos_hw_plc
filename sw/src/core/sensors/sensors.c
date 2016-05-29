#include "utils.h"
#include "bme280.h"
#include "module.h"
#include "switch.h"
#include "sensors.h"

#include <string.h>

#define SENSOR_MAX_NAME_LENGTH		32
#define MAX_SENSOR_COUNT			128
#define MAX_SENSOR_HANDLER_COUNT	16

/**
 * Sensor management
 */
static unsigned char g_max_sensor_id = 0;
static sensor_t *g_sensors[MAX_SENSOR_COUNT];

static unsigned char g_cur_sensor_handler = 0;
static const sensor_handler_t *g_sensors_handler[MAX_SENSOR_HANDLER_COUNT];

int
sensor_handler_register(const sensor_handler_t *sensor_handler)
{
	PANIC_ON(g_cur_sensor_handler == MAX_SENSOR_HANDLER_COUNT, "Too many sensor handlers");
	g_sensors_handler[g_cur_sensor_handler++] = sensor_handler;

	return 0;
}

sensor_t *
sensors_get_by_id(int id)
{
	if (id > g_max_sensor_id)
		return NULL;

	return g_sensors[id];	
};

sensor_t *
sensor_create(sensors_type_t type, const char *name, unsigned char id, const sensors_ops_t *ops, void *data)
{
	sensor_t *s;

	PANIC_ON(id >= MAX_SENSOR_COUNT, "Id is too big");

	if (g_sensors[id] != NULL)
		return NULL;

	s = calloc(1, sizeof(*s));
	if (!s)
		return NULL;

	strncpy(s->name, name, SENSOR_MAX_NAME_LENGTH);
	s->id = id;
	s->type = type;
	s->ops = ops;
	s->data = data;
	g_sensors[id] = s;

	module_sensor_created(s);

	if (id > g_max_sensor_id)
		g_max_sensor_id = id;

	return s;
}


static void
sensors_main_loop()
{
	unsigned int i;

	for (i = 0; i < g_max_sensor_id; i++) {
		if (g_sensors[i] == NULL)
			continue;

		sensor_t *s = g_sensors[i];
		if (s->ops->poll)
			s->ops->poll(s, s->data);
	}
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
	int length, i, j;
	json_value *value;
	const char *name;
	int ret;

        length = section->u.object.length;

        /* Parse each sensors and give them to the appropriate handler */
        for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;
		debug_puts("Adding section %s\r\n", name);
		for (j = 0; j < g_cur_sensor_handler; j++) {
			if (strcmp(name, g_sensors_handler[j]->name))
				continue;

			 ret = g_sensors_handler[j]->json_parse(value);
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
	.sensor_created = NULL,
	.sensor_updated = NULL,
};

void
sensors_init()
{
	bme280_init();
	switch_init();
	module_register(&sensors_module);
}
