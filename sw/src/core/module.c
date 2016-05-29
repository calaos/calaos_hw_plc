#include "debug.h"
#include "utils.h"
#include "queue.h"
#include "module.h"

#include <stdlib.h>

typedef struct registered_module {
	const module_t *mod;
	unsigned long long last_call_time;
	TAILQ_ENTRY(registered_module) link;
} registered_module_t;

static TAILQ_HEAD( ,registered_module) g_registered_module;
static TAILQ_HEAD( ,registered_module) g_active_module;


int module_register(const module_t * mod)
{
	registered_module_t *rmod;

	debug_puts("Registering module %s\r\n", mod->name);
	PANIC_ON(mod->json_parse == NULL, "Missing json_parse callback");

	rmod = malloc(sizeof(registered_module_t));
	rmod->mod = mod;
	
	TAILQ_INSERT_TAIL(&g_registered_module, rmod, link);

	return 0;
}


int module_json_parse(json_value* value)
{
	unsigned int i;
	json_value *section;
	registered_module_t *mod;

	while (!TAILQ_EMPTY(&g_registered_module)) {
		mod = TAILQ_FIRST(&g_registered_module);
		TAILQ_REMOVE(&g_registered_module, mod, link);
		section = config_get_section(value, mod->mod->name);
		if (!section) {
			debug_puts("No json for module %s\r\n", mod->mod->name);
			continue;
		}

		if (mod->mod->json_parse(section) == 0) {
			TAILQ_INSERT_TAIL(&g_active_module, mod, link);
		} else {
			debug_puts("Failed to parse json for module %s\r\n", mod->mod->name);
		}
	}

	return 0;
}

/**
 * Call the module main loop functions
 */
void module_main_loop()
{
	struct registered_module *mod;
	
	TAILQ_FOREACH(mod, &g_active_module, link) {
		if (mod->mod->main_loop) {
			mod->mod->main_loop();
		}
	}
}

int module_sensor_created(sensor_t* s)
{
	struct registered_module *mod;
	
	TAILQ_FOREACH(mod, &g_active_module, link) {
		if (mod->mod->sensor_created) {
			mod->mod->sensor_created(s);
		}
	}

	return 0;
}

int
module_sensor_updated(sensor_t* s, sensor_value_t new_value)
{
	struct registered_module *mod;
	
	TAILQ_FOREACH(mod, &g_active_module, link) {
		if (mod->mod->sensor_updated) {
			mod->mod->sensor_updated(s, new_value);
		}
	}

	return 0;
}
