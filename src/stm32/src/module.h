#ifndef _MODULE_H
#define _MODULE_H

#include "json.h"

/**
 *  Module struct
 */
typedef struct module {
	const char * name;
	void (*main_loop)(void);
	int (*json_parse)(json_value* value);
} module_t;

/**
 * Register a module
 * @param mod Module to register
 * @return 0 if the module was registered without errors, a positive value on error
 */
int module_register(const module_t * mod);


/**
 * Call the module main loop functions
 */
void module_main_loop();

#endif
