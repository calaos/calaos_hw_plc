#ifndef _SENSORS_H
#define _SENSORS_H

#include "json.h"
#include "gpio.h"

#define SENSOR_MAX_NAME_LENGTH	32

/**
 * Sensor types
 */
typedef enum sensors_type {
	SENSORS_TYPE_SWITCH = 0,
	SENSORS_TYPE_HUMIDITY,
	SENSORS_TYPE_TEMP,
	SENSORS_TYPE_PRESSURE,
} sensors_type_t;

typedef struct sensors_ops sensors_ops_t;

/**
 * Sensor struct
 */
typedef struct sensor {
	char name[SENSOR_MAX_NAME_LENGTH];
	const sensors_ops_t *ops;
	unsigned int id;
	sensors_type_t type;
	void *data;
} sensor_t;

/**
 * Sensor value for callbacks
 */
typedef union sensor_value {
	int val_i;
} sensor_value_t;


struct sensors_ops {
	/**
	 * Function call in main loop
	 */
	void (* poll)(sensor_t *, void *data);
	/**
	 * Function call when set is received from controller
	 */
	void (* set)(sensor_t *, void *data, sensor_value_t value);
	/**
	 * Function call when request is received from controller
	 */
	void (* req)(sensor_t *, void *data, sensor_value_t *value);
};

/**
 * Sensor handler struct 
 */
typedef struct sensor_handler {
	/**
	 * Sensor handler name
	 */
	const char * name;
	/**
	 * Parse a sensor json section
	 */
	int (*json_parse)(json_value* value);
} sensor_handler_t;


int
sensor_handler_register(const sensor_handler_t *sensor_handler);

/**
 * Create a sensor
 * @param type Sensor type
 * @param name Sensor name
 * @param id Sensor unique id
 * @param ops Sensor oeprations
 * @param data Sensor private data
 */
sensor_t *
sensor_create(sensors_type_t type, const char *name, unsigned char id, const sensors_ops_t *ops, void *data);


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
static inline sensors_type_t
sensor_get_type(sensor_t *s)
{
	return s->type;
}

/**
 * Get a sensor type
 * @param s Sensor to retrieve info from
 * @return Sensor name
 */
static inline char *
sensor_get_name(sensor_t *s)
{
	return s->name;
}

/**
 * Get a sensor type
 * @param s Sensor to retrieve info from
 * @return Sensor id
 */
static inline int
sensor_get_id(sensor_t *s)
{
	return s->id;
}

void
sensor_set_value(sensor_t *s, sensor_value_t value);

void
sensor_get_value(sensor_t *s, sensor_value_t *value);

/**
 * Init sensor module
 */
void
sensors_init();

#endif
