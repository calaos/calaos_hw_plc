#ifndef _SENSORS_H
#define _SENSORS_H

#include "gpio.h"

#define SENSOR_MAX_NAME_LENGTH	32

/**
 * Sensor types
 */
typedef enum sensors_type {
	SENSORS_TYPE_SWITCH = 0,
} sensors_type_t;

/**
 * Sensor value for callbacks
 */
typedef union sensor_value {
	int val_i;
} sensor_value_t;

typedef struct sensor sensor_t;

/**
 * Init sensor module
 */
void
sensors_init();

/**
 * Get a sensor by its id
 * @param id Id f the sensor to get
 * @return Sensor struct pointer
 */
sensor_t *
sensors_get_by_id(int id);

/**
 * Get a sensor type
 * @param s Sensor to retrieve info from
 * @return Sensor type
 */
sensors_type_t
sensor_get_type(sensor_t *s);

/**
 * Get a sensor type
 * @param s Sensor to retrieve info from
 * @return Sensor name
 */
char *
sensor_get_name(sensor_t *s);


/**
 * Get a sensor type
 * @param s Sensor to retrieve info from
 * @return Sensor id
 */
int
sensor_get_id(sensor_t *s);


void
sensor_set_value(sensor_t *s, sensor_value_t value);

void
sensor_get_value(sensor_t *s, sensor_value_t *value);

#endif
