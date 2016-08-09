#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "HAL.h"
#include "debug.h"
#include "config.h"
#include "module.h"
#include "communication.h"

#define MAX_BUF_SIZE	128


unsigned int g_debug_enabled = 0;

static SLIST_HEAD( ,com_handler) g_com_handlers = SLIST_HEAD_INITIALIZER();

static char g_io_buffer[MAX_BUF_SIZE];



void
generic_send(com_type_t com_type, const char *str)
{
	struct com_handler *hdler;

	if (com_type == COM_TYPE_STD)
		hal_serial_puts(g_io_buffer);
	else if (com_type == COM_TYPE_DBG)
		hal_debug_puts(g_io_buffer);

	SLIST_FOREACH(hdler, &g_com_handlers, link) {
		hdler->put_str(com_type, g_io_buffer);
	}
}


void
generic_puts(com_type_t com_type, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	vsnprintf(g_io_buffer, sizeof(g_io_buffer), format, args);
	va_end(args);
	
	generic_send(com_type, g_io_buffer);
}

void
dbg_puts(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	vsnprintf(g_io_buffer, sizeof(g_io_buffer), format, args);
	va_end(args);

	generic_send(COM_TYPE_DBG, g_io_buffer);
}


void
communication_register(com_handler_t *hdler)
{
	SLIST_INSERT_HEAD(&g_com_handlers, hdler, link);
}

static int
com_json_parse(json_value* section)
{
        unsigned int i, length;
	json_value *value;
	char *name;
	int baudrate = DEFAULT_BAUDRATE;

	length = section->u.object.length;
	for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;

		if (strcmp(name, "debug") == 0) {
			g_debug_enabled = value->u.integer;
		} else if (strcmp(name, "baudrate") == 0) {
			baudrate = value->u.integer;
		}
	}

	std_puts("Debug enabled: %d, setting serial baudrate to %d\r\n", g_debug_enabled, baudrate);
	hal_serial_set_baudrate(baudrate);

	return 0;
}

/**
 * Module
 */
static const module_t com_module = {
	.name = "communication",
	.main_loop = NULL,
	.json_parse = com_json_parse,
};


void
communication_init()
{
	module_register(&com_module);
}


