#ifndef _MODULE_H
#define _MODULE_H

#include "json.h"
#include "queue.h"
#include "config.h"
#include "sensors.h"
#include "communication.h"

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

typedef enum handle_message_ret {
	MESSAGE_HANDLED = 0,
	MESSAGE_STOP_PROCESSING,
	MESSAGE_IGNORED,
} handle_message_ret_t;


typedef void (*command_handler_t)(int argc, char **argv);

typedef struct module_command {
	const char *name;
	const char *help;
	command_handler_t hdler;
} module_command_t;

#define MODULE_COMMANDS(__cmds)			\
	.commands = __cmds,			\
	.command_count = ARRAY_SIZE(__cmds)

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
	 * Command related stuff
	 */
	const module_command_t *commands;
	unsigned int command_count;

	/**
	 * Module main loop hook
	 */
	void (*main_loop)(void);
	/**
	 * Handle message callback
	 * Allow the module to catch some specific message and handle them
	 * @param buf Buffer to parse
	 * @param len Buffer length
	 */
	handle_message_ret_t (*handle_message)(char *buf, unsigned int len);

	/**
	 * Parse a json section
	 * @param value Json value
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


void
module_handle_message(com_type_t com_type, char *buf, unsigned int len);

#endif
