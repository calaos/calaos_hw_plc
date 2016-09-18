#include "debug.h"
#include "utils.h"
#include "queue.h"
#include "module.h"

#include <stdlib.h>
#include <string.h>

#define MAX_CMD_ARGS	10

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

	dbg_log("Registering module %s\n", mod->name);

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
			dbg_log("No json for module %s\n", rmod->mod->name);
			continue;
		}

		if (rmod->mod->json_parse(section) == 0) {
			TAILQ_INSERT_TAIL(&g_active_module, rmod, link);
		} else {
			dbg_log("Failed to parse json for module %s\n", rmod->mod->name);
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

static int
string_to_args(char *str, char **args) {

	int args_count = 0;

	while(*str != '\0') {
		/* Skip spaces */
		while (*str && *str == ' ' && *str != '\t')
			*str++ = '\0';
		if (*str == '\0')
			break;
		args[args_count] = str;
		args_count++;
		if (args_count == MAX_CMD_ARGS)
			return args_count;

		/* Go to next argument */
		while (*str != '\0' && *str != ' ' &&  *str != '\t') {
			str++;
		}
	}

	return args_count;
}

static void
display_help()
{
	struct registered_module *rmod;
	const module_t *mod;
	unsigned int i;

	dbg_puts("Available commands:\n");
	dbg_puts("  - help: display this help\n");

	TAILQ_FOREACH(rmod, &g_active_module, link) {
		mod = rmod->mod;
		for (i = 0; i < mod->command_count; i++) {
			dbg_puts("  - %s: %s\n", mod->commands[i].name, mod->commands[i].help);
		}
	}
}

void
module_handle_command(char *buf, unsigned int len)
{
	struct registered_module *rmod;
	unsigned int i;
	const module_t *mod;
	char *cmd_args[MAX_CMD_ARGS] = {NULL};
	int argc;

	if (strncmp(buf, "help", 4) == 0) {
		display_help();
		return;
	}

	/* Split the buffer */
	argc = string_to_args(buf, cmd_args);
	if (argc == 0)
		return;

	/* split the command in multiple tokens */
	TAILQ_FOREACH(rmod, &g_active_module, link) {
		mod = rmod->mod;
		for (i = 0; i < mod->command_count; i++) {
			if (strncmp(mod->commands[i].name, cmd_args[0], strlen(mod->commands[i].name)) == 0) {
				mod->commands[i].hdler(argc, cmd_args);
				dbg_puts("$ ");
				return;
			}
		}
	}
	dbg_puts("Unknow command %s\n", cmd_args[0]);
	display_help();
	dbg_puts("$ ");
}

void
module_handle_message(com_type_t com_type, char *buf, unsigned int len)
{
	struct registered_module *rmod;
	handle_message_ret_t ret;

	if (com_type == COM_TYPE_STD) {
		TAILQ_FOREACH(rmod, &g_active_module, link) {
			if (rmod->mod->handle_message) {
				ret = rmod->mod->handle_message(buf, len);
				if (ret == MESSAGE_STOP_PROCESSING)
					return;
			}
		}
	} else {
		module_handle_command(buf, len);
	}
}
