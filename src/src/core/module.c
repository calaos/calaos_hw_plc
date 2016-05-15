#include "debug.h"
#include "module.h"

#include <stdlib.h>

#define MAX_MODULES	10

static const module_t *modules[MAX_MODULES];
static unsigned int module_count = 0;

int module_register(const module_t * mod)
{
	if (module_count == MAX_MODULES)
		return 1;

	debug_puts("Registering module %s\r\n", mod->name);

	modules[module_count++] = mod;

	return 0;
}

/**
 * Call the module main loop functions
 */
void module_main_loop()
{
	unsigned int i;

	for( i = 0; i < module_count; i++) {
		if (modules[i]->main_loop) {
			modules[i]->main_loop();
		}
	}
}

int module_json_parse(json_value* value)
{
	unsigned int i;

	for( i = 0; i < module_count; i++) {
		if (modules[i]->json_parse) {
			modules[i]->json_parse(value);
		}
	}

	return 0;
}

int module_sensor_created(sensor_t* s)
{
	unsigned int i;

	for( i = 0; i < module_count; i++) {
		if (modules[i]->sensor_created) {
			modules[i]->sensor_created(s);
		}
	}

	return 0;
}

int
module_sensor_updated(sensor_t* s, sensor_value_t new_value)
{
	unsigned int i;

	for( i = 0; i < module_count; i++) {
		if (modules[i]->sensor_updated) {
			modules[i]->sensor_updated(s, new_value);
		}
	}

	return 0;
}
