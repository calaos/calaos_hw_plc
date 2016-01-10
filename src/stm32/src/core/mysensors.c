#include "HAL.h"
#include "gpio.h"
#include "debug.h"
#include "utils.h"
#include "module.h"
#include "mysensors.h"
#include "sensors.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Node id requested from controller
 */
static unsigned char g_assigned_node_id = 0;

static char g_mysensors_str[MYSENSOR_MAX_MSG_LENGTH];
static unsigned char g_str_cur_index = 0;

static int mysensors_serial_get_message(char *str)
{
	int ret;
	char c;

	ret = hal_serial_getc(&c);
	if (ret == 0)
		return 0;

	if (c == '\n') {
		g_mysensors_str[g_str_cur_index] = '\0';
		g_str_cur_index = 0;
		strcpy(str, g_mysensors_str);
		debug_puts("Got mysensors query: %s\n", g_mysensors_str);
		return 1;
	}

	g_mysensors_str[g_str_cur_index++] = c;
	if (g_str_cur_index == MYSENSOR_MAX_MSG_LENGTH) {
		debug_puts("Received string too long from controller, discarding\r\n");
		g_str_cur_index = 0;
	}

	return 0;
}


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

static int mysensors_handle_serial()
{
	char query[MYSENSOR_MAX_MSG_LENGTH];
	unsigned char child_sensor_id, __unused__ message_type, ack, __unused__ subtype;
	char *split_str[6], __unused__ *payload;
	sensor_t *sensor;

	/* Check for serial message */
	if (!mysensors_serial_get_message(query))
		return 0;

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
		debug_puts("Ack requested\r\n");
	}

	return 1;
}

/**
 * FIXME: generate these functions
 */
static void
mysensors_send_message_str(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, char *payload)
{
	serial_puts("%d;%d;%d;%d;%d;%s\n", node_id, child_sensor_id, message_type, ack, sub_type, payload);
}

static void
mysensors_send_message_int(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, int value)
{
	serial_puts("%d;%d;%d;%d;%d;%d\n", node_id, child_sensor_id, message_type, ack, sub_type, value);
}

static void
mysensors_update_value_int(sensor_t *s, mysensors_datatype_t dt, int value)
{
	mysensors_send_message_int(g_assigned_node_id, sensor_get_id(s), SET_VARIABLE, REQUEST, dt, value);
}

static int
mysensors_json_parse_section(json_value* section)
{
	unsigned int i;
	json_value* entry;
	if (section == NULL || section->type != json_object)
		return -1;

        for (i = 0; i < section->u.object.length; i++) {
		entry = section->u.object.values[i].value;
		if (strcmp(section->u.object.values[i].name, "node_id") == 0) {
			g_assigned_node_id = entry->u.integer;
			debug_puts("Node id: %d\n", g_assigned_node_id);
		}
        }

	return 0;
}

static int
mysensors_json_parse(json_value* value)
{
        json_value *section;
        
        section = config_get_section(value, "mysensors");
	if (section)
		mysensors_json_parse_section(section);

	if (g_assigned_node_id == 0) {
		mysensors_send_message_str(0, 0, INTERNAL, REQUEST, I_ID_REQUEST, "1.0");
		/* FIXME: Wait message */
		g_assigned_node_id = 1;
	}

        return 0;
}

static void
mysensor_sensor_created(sensor_t *s)
{
	mysensors_sensortype_t type;
	switch (sensor_get_type(s)) {
		case SENSORS_TYPE_SWITCH:
			type = S_LIGHT; break;
		default:
			return;
	};
	mysensors_send_message_str(g_assigned_node_id, sensor_get_id(s), PRESENTATION, REQUEST, type, sensor_get_name(s));
}

static void
mysensor_sensor_updated(sensor_t *s, sensor_value_t value)
{
	mysensors_update_value_int(s, V_STATUS, value.val_i);
}


static void
mysensors_main_loop()
{
	mysensors_handle_serial();
}

const module_t mysensors_module = {
	.name = "display",
	.main_loop = mysensors_main_loop,
	.json_parse = mysensors_json_parse,
	.sensor_created = mysensor_sensor_created,
	.sensor_updated = mysensor_sensor_updated,
};

void
mysensors_init()
{
	module_register(&mysensors_module);
}
