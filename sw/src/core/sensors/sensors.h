#ifndef _SENSORS_H
#define _SENSORS_H

#include "json.h"
#include "gpio.h"
#include "queue.h"

#define SENSOR_MAX_NAME_LENGTH	32

typedef struct sensor sensor_t;

/**
 * Sensor types
 */
typedef enum sensors_type {
	SENSORS_TYPE_SWITCH = 0,
	SENSORS_TYPE_HUMIDITY,
	SENSORS_TYPE_TEMP,
	SENSORS_TYPE_PRESSURE,
	SENSORS_TYPE_LIGHT,
	SENSORS_TYPE_COUNT,
} sensors_type_t;

/**
 * Constraint types
 */
typedef enum sensors_constraint_type {
	SENSORS_CST_TYPE_NOR = 0,
} sensors_constraint_type_t;

/**
 * NOR constraint
 */
typedef struct sensors_constraint_nor {
	sensor_t *s1;
	sensor_t *s2;
} sensors_constraint_nor_t;

/**
 * Constraint union
 */
typedef struct sensor_constraint {
	sensors_constraint_type_t type;
	union {
		sensors_constraint_nor_t nor;
	} data;

	/* Link list link */
	SLIST_ENTRY(sensor_constraint) link;
} sensor_constraint_t;

typedef struct sensor_constraint_ptr {
	sensor_constraint_t *cst;
	SLIST_ENTRY(sensor_constraint_ptr) link;
} sensor_constraint_ptr_t;

typedef struct sensors_ops sensors_ops_t;

/**
 * Sensor value for callbacks
 */
typedef union sensor_value {
	int val_i;
	float val_f;
} sensor_value_t;


/**
 * Sensor struct
 */
struct sensor {
	char name[SENSOR_MAX_NAME_LENGTH];
	const sensors_ops_t *ops;
	sensor_value_t val;
	unsigned int id;
	sensors_type_t type;
	void *data;

	SLIST_HEAD(,sensor_constraint_ptr) constraints;
};

struct sensors_ops {
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
	/**
	 * Function call in main loop
	 */
	void (* poll)();

	/* Link list link */
	SLIST_ENTRY(sensor_handler) link;
} sensor_handler_t;

/**
 * Register a sensor handler
 * @param sensor_handler Operations of the sensor handler
 * @return 0 on success, a positive value on error
 */
int
sensors_register_handler(sensor_handler_t *sensor_handler);

typedef struct sensor_watcher {
	/**
	 * Call back when sensor has been created
	 */
	void (*sensor_created)(sensor_t *s);
	/**
	 * Call back when sensor has been updated (new value);
	 */
	void (*sensor_updated)(sensor_t *s, sensor_value_t new_value);

	/* Link list link */
	SLIST_ENTRY(sensor_watcher) link;
}sensor_watcher_t;

/**
 * Register a sensor watcher
 * @param sensor_watcher Operations of the sensor watcher
 * @return 0 on success, a positive value on error
 */
int
sensors_register_watcher(sensor_watcher_t *sensor_watcher);

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

/**
 * Set a sensor value
 * @param s Sensor to set
 * @param value Value to set 
 */
void
sensor_set_value(sensor_t *s, sensor_value_t value);

/**
 * Get a sensor value
 * @param s Sensor to get value from
 * @param[out] value Sensor value 
 */
void
sensor_get_value(sensor_t *s, sensor_value_t *value);

/**
 * 
 */
int
sensors_sensor_update(sensor_t* s, sensor_value_t new_value);

/**
 * Init sensor module
 */
void
sensors_init();

#endif
