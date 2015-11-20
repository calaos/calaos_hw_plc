#include "HAL.h"
#include "mysensor.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static unsigned int current_sensor_id = 0;


static int mysensor_send_message(uint16_t node_id,
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

void mysensor_init()
{
	mysensor_send_message(0, 0, INTERNAL, 0, 0, "");

	//~ hal_serial_gets
}


mysensor_sensor_t *mysensor_create_sensor(mysensor_sensortype_t type, const char *name)
{
	mysensor_sensor_t *s;

	s = malloc(sizeof(*s));
	if (!s)
		return NULL;

	strncpy(s->name, name, MYSENSOR_MAX_NAME_LENGTH);
	s->node_id = current_sensor_id++;

	return s;
}
