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

static TAILQ_HEAD( ,registered_module) g_registered_module = TAILQ_HEAD_INITIALIZER(g_registered_module);
static TAILQ_HEAD( ,registered_module) g_active_module = TAILQ_HEAD_INITIALIZER(g_active_module);


int module_register(const module_t * mod)
{
	registered_module_t *rmod;

	debug_puts("Registering module %s\r\n", mod->name);

	rmod = malloc(sizeof(registered_module_t));
	rmod->mod = mod;
	
	TAILQ_INSERT_TAIL(&g_registered_module, rmod, link);

	return 0;
}


int module_json_parse(json_value* value)
{
	json_value *section;
	registered_module_t *rmod;

	while (!TAILQ_EMPTY(&g_registered_module)) {
		rmod = TAILQ_FIRST(&g_registered_module);
		TAILQ_REMOVE(&g_registered_module, rmod, link);
		if (!rmod->mod->json_parse) {
			TAILQ_INSERT_TAIL(&g_active_module, rmod, link);
		}

		section = config_get_section(value, rmod->mod->name);
		if (!section) {
			debug_puts("No json for module %s\r\n", rmod->mod->name);
			continue;
		}

		if (rmod->mod->json_parse(section) == 0) {
			TAILQ_INSERT_TAIL(&g_active_module, rmod, link);
		} else {
			debug_puts("Failed to parse json for module %s\r\n", rmod->mod->name);
			free(rmod);
		}
	}

	return 0;
}

/**
 * Call the module main loop functions
 */
void module_main_loop()
{
	struct registered_module *rmod;
	
	TAILQ_FOREACH(rmod, &g_active_module, link) {
		if (rmod->mod->main_loop) {
			rmod->mod->main_loop();
		}
	}
}
