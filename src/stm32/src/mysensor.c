#include "HAL.h"
#include "mysensor.h"
#include "initcall.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static unsigned int current_sensor_id = 0;
static unsigned int assigned_node_id;

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


void
mysensor_init()
{
	mysensor_send_raw_message(0, 0, INTERNAL, REQUEST, 0, "");
	/* Wait message */
	assigned_node_id = 1;
}
