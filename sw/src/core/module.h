#ifndef _MODULE_H
#define _MODULE_H

#include "json.h"
#include "queue.h"
#include "config.h"
#include "sensors.h"

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

/**
 *  Module struct
 */
typedef struct module {
	/**
	 * Module name
	 */
	const char * name;
	/**
	 * Polling time
	 */
	unsigned int poll_time;
	/**
	 * Module main loop hook
	 */
	void (*main_loop)(void);
	/* Parse a json section
	 * return 0 if ok, or a negative value in case of error */
	int (*json_parse)(json_value* value);
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


#endif
