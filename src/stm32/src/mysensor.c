#include "HAL.h"
#include "debug.h"
#include "utils.h"
#include "module.h"
#include "mysensor.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static unsigned int current_sensor_id = 0;
static unsigned int assigned_node_id;

static const char *sensor_type_str[] = {
    [0] = "S_DOOR",                 // Door and window sensors
    [1] = "S_MOTION",               // Motion sensors
    [2] = "S_SMOKE",                // Smoke sensor
    [3] = "S_LIGHT",                // Light Actuator (on/off)
    [4] = "S_DIMMER",               // Dimmable device of some kind
    [5] = "S_COVER",                // Window covers or shades
    [6] = "S_TEMP",                 // Temperature sensor
    [7] = "S_HUM",                  // Humidity sensor
    [8] = "S_BARO",                 // Barometer sensor (Pressure)
    [9] = "S_WIND",                 // Wind sensor
    [10] = "S_RAIN",                // Rain sensor
    [11] = "S_UV",                  // UV sensor
    [12] = "S_WEIGHT",              // Weight sensor for scales etc.
    [13] = "S_POWER",               // Power measuring device, like power meters
    [14] = "S_HEATER",              // Heater device
    [15] = "S_DISTANCE",            // Distance sensor
    [16] = "S_LIGHT_LEVEL",         // Light sensor
    [17] = "S_ARDUINO_NODE",        // Arduino node device
    [18] = "S_ARDUINO_RELAY",       // Arduino relaying node device
    [19] = "S_LOCK",                // Lock device
    [20] = "S_IR",                  // Ir sender/receiver device
    [21] = "S_WATER",               // Water meter
    [22] = "S_AIR_QUALITY",         // Air quality sensor e.g. MQ-2
    [23] = "S_CUSTOM",              // Use this for custom sensors where no other fits.
    [24] = "S_DUST",                // Dust level sensor
    [25] = "S_SCENE_CONTROLLER",    // Scene controller device
};


static int mysensor_typestr_to_type(const char *name)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(sensor_type_str); i++) {
		if (strcmp(sensor_type_str[i], name) == 0) {
			return i;
		}
	}

	return -1;
}

static int
mysensor_send_raw_message(uint16_t node_id,
				uint8_t child_sensor_id,
				uint16_t message_type,
				uint8_t ack,
				uint16_t sub_type,
				char *payload)
{
	char msg[MYSENSOR_MAX_MSG_LENGTH];

	sprintf(msg, "%d;%d;%d;%d;%d;%s\n", node_id, child_sensor_id, message_type, ack, sub_type, payload);

	return hal_serial_puts(msg);
}

static int
mysensor_send_message(uint8_t child_sensor_id,
				uint16_t message_type,
				uint8_t ack,
				uint16_t sub_type,
				char *payload)
{
	return mysensor_send_raw_message(assigned_node_id, child_sensor_id, message_type, ack, sub_type, payload);
}

static int
mysensor_send_presentation(mysensor_sensor_t * s)
{
	return mysensor_send_message(s->node_id, PRESENTATION, REQUEST, s->type, s->name);
}

mysensor_sensor_t *
mysensor_create_sensor(mysensor_sensortype_t type, const char *name)
{
	mysensor_sensor_t *s;

	s = malloc(sizeof(*s));
	if (!s)
		return NULL;

	strncpy(s->name, name, MYSENSOR_MAX_NAME_LENGTH);
	s->node_id = current_sensor_id++;
	s->type = type;
	mysensor_send_presentation(s);

	return s;
}

int
mysensor_update_value_float(mysensor_sensor_t *s, mysensor_datatype_t dt, float value)
{
	char payload[10];

	sprintf(payload, "%.02f", value);

	return mysensor_send_message(s->node_id, SET_VARIABLE, REQUEST, dt, payload);
}

int
mysensor_update_value_str(mysensor_sensor_t *s, mysensor_datatype_t dt, char *str)
{
	return mysensor_send_message(s->node_id, SET_VARIABLE, REQUEST, dt, str);
}


static int
mysensor_config_handler(const char* section, const char* name, const char* value)
{
	static bool s_fill = 0;
	static int s_type;
	static char s_name[MYSENSOR_MAX_NAME_LENGTH];

	/* We only handle sensor sections */
	if (strcmp(section, "sensor") != 0)
		return 0;

	/* New sensor section */
	if (name == NULL) {
		/* If we are filling a sensor */
		if (s_fill) {
			mysensor_create_sensor(s_type, s_name);
			s_fill = false;
		} else {
			s_fill = true;
		}
	} else {
		if (strcmp(name, "type") == 0) {
			mysensor_typestr_to_type(value);
		} else if (strcmp(name, "name") == 0) {
			strncpy(s_name, value, MYSENSOR_MAX_NAME_LENGTH);
		} else {
			debug_puts("Unknown option %s\r\n", name);
		}
	}

	return 1;
}

const module_t mysensor_module = {
	.name = "mysensor",
	.main_loop = NULL,
	.config_handler = mysensor_config_handler,
};

void
mysensor_init()
{
	module_register(&mysensor_module);

	mysensor_send_raw_message(0, 0, INTERNAL, REQUEST, 0, "");
	/* Wait message */
	assigned_node_id = 1;
}
