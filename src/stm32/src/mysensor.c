#include "HAL.h"
#include "debug.h"
#include "utils.h"
#include "module.h"
#include "mysensor.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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


int
mysensor_typestr_to_type(const char *name)
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
mysensor_send_message_str(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, char *payload)
{
	char msg[MYSENSOR_MAX_MSG_LENGTH];
	sprintf(msg, "%d;%d;%d;%d;%d;%s\n", node_id, child_sensor_id, message_type, ack, sub_type, payload);
	return hal_serial_puts(msg);
}

static int
mysensor_send_message_float(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, float value)
{
	char msg[MYSENSOR_MAX_MSG_LENGTH];
	sprintf(msg, "%d;%d;%d;%d;%d;%f\n", node_id, child_sensor_id, message_type, ack, sub_type, value);
	return hal_serial_puts(msg);
}

int
mysensor_update_value_float(mysensor_sensor_t *s, mysensor_datatype_t dt, float value)
{
	return mysensor_send_message_float(assigned_node_id, s->node_id, SET_VARIABLE, REQUEST, dt, value);
}

int
mysensor_update_value_str(mysensor_sensor_t *s, mysensor_datatype_t dt, char *str)
{
	return mysensor_send_message_str(assigned_node_id, s->node_id, SET_VARIABLE, REQUEST, dt, str);
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
	mysensor_send_message_str(assigned_node_id, s->node_id, PRESENTATION, REQUEST, s->type, s->name);

	return s;
}


static int
mysensor_json_parse_sensor(json_value* sensor)
{
	int length, i;
	const char *name;
	char s_name[MYSENSOR_MAX_NAME_LENGTH];
	int s_type = -1;
	json_value *value;
        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			strcpy(s_name, value->u.string.ptr);
		} else if (strcmp(name, "pin") == 0) {

		} else if (strcmp(name, "type") == 0) {
			s_type = mysensor_typestr_to_type(value->u.string.ptr);
		}
        }

	mysensor_create_sensor(s_type, s_name);
	
	return 0;
}

static int
mysensor_json_parse_sensors(json_value* array)
{
	int length, i;
	json_value* sensor;
	if (array == NULL || array->type != json_array)
		return -1;

	debug_puts("Got sensors section\r\n");

        length = array->u.array.length;
        for (i = 0; i < length; i++) {
		sensor = array->u.array.values[i];
		mysensor_json_parse_sensor(sensor);
        }
	
	return 0;
}

static int
mysensor_json_parse(json_value* value)
{
        int length, x;
	if (value == NULL || value->type != json_object) {
                return -1;
        }
     
        length = value->u.object.length;
        for (x = 0; x < length; x++) {
		/* We only care about sensor section*/
		if (strcmp(value->u.object.values[x].name,"sensors") != 0)
			continue;

                return mysensor_json_parse_sensors(value->u.object.values[x].value);
        }

        return -1;
}

const module_t mysensor_module = {
	.name = "mysensor",
	.main_loop = NULL,
	.json_parse = mysensor_json_parse,
};

void
mysensor_init()
{
	module_register(&mysensor_module);

	mysensor_send_message_str(0, 0, INTERNAL, REQUEST, 0, "1.0");
	/* Wait message */
	assigned_node_id = 1;
}
