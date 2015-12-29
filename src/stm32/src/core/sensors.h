#ifndef _SENSORS_H_
#define _SENSORS_H_

#include "gpio.h"

#define SENSOR_MAX_NAME_LENGTH	32

typedef enum sensors_type {
	SENSORS_TYPE_SWITCH = 0,
} sensors_type_t;

typedef struct sensor sensor_t;

void
sensors_init();

sensor_t *
sensors_get_by_id(int id);

#endif
