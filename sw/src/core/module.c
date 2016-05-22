#include "debug.h"
#include "module.h"

#include <stdlib.h>

#define MAX_MODULES	15

typedef struct registered_module {
	const module_t *mod;
	unsigned long long last_call_time;
} registered_module_t;

static const module_t *registered_modules[MAX_MODULES];
static unsigned int registered_mod_count = 0;

static registered_module_t active_modules[MAX_MODULES] = {{NULL, 0}};
static unsigned int active_mod_count = 0;


int module_register(const module_t * mod)
{
	if (registered_mod_count == MAX_MODULES)
		return 1;

	debug_puts("Registering module %s\r\n", mod->name);

	registered_modules[registered_mod_count] = mod;
	registered_mod_count++;

	return 0;
}


int module_json_parse(json_value* value)
{
	unsigned int i;
	json_value *section;
	const module_t *mod;

	for( i = 0; i < registered_mod_count; i++) {
		mod = registered_modules[i];
		if (mod->json_parse) {
			section = config_get_section(value, mod->name);
			if (!section) {
				debug_puts("No json for module %s\r\n", mod->name);
				continue;
			}

			if (mod->json_parse(section) == 0) {
				active_modules[active_mod_count++].mod = mod;
			} else {
				debug_puts("Failed to parse json for module %s\r\n", mod->name);
			}
		}
	}

	return 0;
}

/**
 * Call the module main loop functions
 */
void module_main_loop()
{
	unsigned int i;

	for( i = 0; i < active_mod_count; i++) {
		if (active_modules[i].mod->main_loop) {
			active_modules[i].mod->main_loop();
		}
	}
}

int module_sensor_created(sensor_t* s)
{
	unsigned int i;

	for( i = 0; i < active_mod_count; i++) {
		if (active_modules[i].mod->sensor_created) {
			active_modules[i].mod->sensor_created(s);
		}
	}

	return 0;
}

int
module_sensor_updated(sensor_t* s, sensor_value_t new_value)
{
	unsigned int i;

	for( i = 0; i < active_mod_count; i++) {
		if (active_modules[i].mod->sensor_updated) {
			active_modules[i].mod->sensor_updated(s, new_value);
		}
	}

	return 0;
}
