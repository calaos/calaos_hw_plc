#ifndef _MODULE_H
#define _MODULE_H

#include "json.h"
#include "sensors.h"
#include "config.h"

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

/**
 *  Module struct
 */
typedef struct module {
	const char * name;
	void (*main_loop)(void);
	int (*json_parse)(json_value* value);
	/* Sensor related function for modules to listen on sensor events */
	void (*sensor_created)(sensor_t *s);
	void (*sensor_updated)(sensor_t *s, sensor_value_t new_value);
} module_t;

/**
 * Register a module
 * @param mod Module to register
 * @return 0 if the module was registered without errors, a positive value on error
 */
int
module_register(const module_t * mod);

/**
 * Call the module main loop functions
 */
void
module_main_loop();

/**
 * Call the module json parsing function
 * @param value The json tree
 * @return 1 if the module handled the json or 0 if not
 */
int
module_json_parse(json_value* value);

int
module_sensor_created(sensor_t* s);

int
module_sensor_updated(sensor_t* s, sensor_value_t new_value);

#endif
