#include "HAL.h"
#include "gpio.h"
#include "debug.h"
#include "utils.h"
#include "module.h"
#include "sensors.h"
#include "network.h"
#include "mysensors.h"
#include "communication.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Node id requested from controller
 */
static unsigned char g_assigned_node_id = 0;

static int mysensors_split_message(char *str, char *split_str[6])
{
	int i;
	char *next = str;

	for (i = 0; i < 6; i++) {
		split_str[i] = next;
		if (i == 5)
			break;

		next = strchr(next, ';');
		if (next == NULL)
			return 1;
		*next = '\0';
		next++;
	}

	return 0;
}

static void mysensors_set_sensor(sensor_t *s, __unused__ int subtype, char *payload)
{
	sensor_value_t value;
	if (sensor_get_type(s) == SENSORS_TYPE_SWITCH) {
		value.val_i = atoi(payload);
		sensor_set_value(s, value);
	}
}

int mysensors_parse_message(char *query)
{
	unsigned char child_sensor_id, message_type, ack, subtype;
	char *split_str[6], *payload;
	sensor_t *sensor;

	if (mysensors_split_message(query, split_str) != 0)
		return 0;

	if (atoi(split_str[0]) != g_assigned_node_id)
		return 0;

	child_sensor_id = atoi(split_str[1]);

	sensor = sensors_get_by_id(child_sensor_id);
	if (sensor == NULL)
		return 0;

	message_type = atoi(split_str[2]);
	ack = atoi(split_str[3]);
	subtype = atoi(split_str[4]);
	payload = split_str[5];

	switch (message_type) {
		case SET_VARIABLE:
			mysensors_set_sensor(sensor, subtype, payload);
		break;
		case REQUEST_VARIABLE:
		break;
	};

	if (ack) {
		dbg_log("Ack requested\r\n");
	}

	return 1;
}


#define MYSENSORS_MSG_FORMAT	"%d;%d;%d;%d;%d;"

static void mysensor_send_message(char *str)
{
	std_puts(str);
}

/**
 * FIXME: generate or make these function generic
 */
static void
mysensors_serial_send_str(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, char *payload)
{
	char buffer[MYSENSOR_MAX_MSG_LENGTH];

	snprintf(buffer, MYSENSOR_MAX_MSG_LENGTH, MYSENSORS_MSG_FORMAT "%s\n", node_id, child_sensor_id, message_type, ack, sub_type, payload);
	mysensor_send_message(buffer);
}

static void
mysensors_send_int(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, int value)
{
	char buffer[MYSENSOR_MAX_MSG_LENGTH];

	snprintf(buffer, MYSENSOR_MAX_MSG_LENGTH, MYSENSORS_MSG_FORMAT "%d\n", node_id, child_sensor_id, message_type, ack, sub_type, value);
	mysensor_send_message(buffer);
}

static void
mysensors_send_float(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, float value)
{
	char buffer[MYSENSOR_MAX_MSG_LENGTH];

	snprintf(buffer, MYSENSOR_MAX_MSG_LENGTH, MYSENSORS_MSG_FORMAT "%.2f\n", node_id, child_sensor_id, message_type, ack, sub_type, value);
	mysensor_send_message(buffer);
}

static int
mysensors_json_parse_section(json_value* section)
{
	unsigned int i;
	json_value* entry;
	char *name;
	if (section->type != json_object)
		return -1;

        for (i = 0; i < section->u.object.length; i++) {
		entry = section->u.object.values[i].value;
		name = section->u.object.values[i].name;
		if (strcmp(name, "node_id") == 0) {
			g_assigned_node_id = entry->u.integer;
			dbg_log("Node id: %d\r\n", g_assigned_node_id);
		}
        }

	return 0;
}

static const unsigned int
sensor_to_mysensor[SENSORS_TYPE_COUNT] = 
{
	[SENSORS_TYPE_SWITCH] = S_LIGHT,
	[SENSORS_TYPE_HUMIDITY] = S_HUM,
	[SENSORS_TYPE_TEMP] = S_TEMP,
	[SENSORS_TYPE_PRESSURE] = S_BARO,
	[SENSORS_TYPE_LIGHT] = S_LIGHT,
};

static void
mysensor_sensor_created(sensor_t *s)
{
	mysensors_sensortype_t type = sensor_get_type(s);

	mysensors_serial_send_str(g_assigned_node_id, sensor_get_id(s), PRESENTATION, REQUEST, type, sensor_get_name(s));
}

static void
mysensor_sensor_updated(sensor_t *s, sensor_value_t value)
{
	switch (sensor_get_type(s)) {
		case SENSORS_TYPE_SWITCH:
			mysensors_send_int(g_assigned_node_id, sensor_get_id(s), SET_VARIABLE, REQUEST, V_STATUS, value.val_i);
			break;
		case SENSORS_TYPE_LIGHT:
			mysensors_send_int(g_assigned_node_id, sensor_get_id(s), SET_VARIABLE, REQUEST, V_LIGHT_LEVEL, value.val_i);
			break;
		case SENSORS_TYPE_HUMIDITY:
			mysensors_send_float(g_assigned_node_id, sensor_get_id(s), SET_VARIABLE, REQUEST, V_HUM, value.val_f);
			break;
		case SENSORS_TYPE_TEMP:
			mysensors_send_float(g_assigned_node_id, sensor_get_id(s), SET_VARIABLE, REQUEST, V_TEMP, value.val_f);
			break;
		case SENSORS_TYPE_PRESSURE:
			mysensors_send_float(g_assigned_node_id, sensor_get_id(s), SET_VARIABLE, REQUEST, V_PRESSURE, value.val_f);
			break;
		default:
			break;
	}
}

static sensor_watcher_t mysensor_watcher = {
	.sensor_created = mysensor_sensor_created,
	.sensor_updated = mysensor_sensor_updated,
};


int mysensor_handle_message(com_type_t com_type, char *buf, unsigned int len)
{
	if (com_type == COM_TYPE_STD) {
		if (mysensors_parse_message(buf) == 1) {
			return MESSAGE_STOP_PROCESSING;
		}
	}
	
	return MESSAGE_IGNORED;		
}

static int
mysensors_json_parse(json_value* value)
{
	if (mysensors_json_parse_section(value) != 0)
		return 1;

	if (g_assigned_node_id == 0) {
		mysensors_serial_send_str(0, 0, INTERNAL, REQUEST, I_ID_REQUEST, "1.0");
		/* FIXME: Wait message */
		g_assigned_node_id = 1;
	}
	
	sensors_register_watcher(&mysensor_watcher);

        return 0;
}

static const module_t mysensors_module = {
	.name = "mysensors",
	.main_loop = NULL,
	.json_parse = mysensors_json_parse,
	.handle_message = mysensor_handle_message,
};

void
mysensors_init()
{
	module_register(&mysensors_module);
}
