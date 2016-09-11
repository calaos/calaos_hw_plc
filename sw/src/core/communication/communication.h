#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "json.h"
#include "queue.h"

#define DEFAULT_BAUDRATE	115200

typedef enum com_type {
	COM_TYPE_STD = 0,
	COM_TYPE_DBG,
	COM_TYPE_COUNT,
} com_type_t;

void
generic_puts(com_type_t com_type, const char *format, ...);

#define std_puts(format, ...) generic_puts(COM_TYPE_STD, format, ##__VA_ARGS__)

void
dbg_puts(const char *format, ...);

typedef struct com_handler {
	/**
	 * Com handler name
	 */
	const char *name;
	/**
	 * Output a standard string
	 */
	void (*put_str)(com_type_t com_type, const char *str);

	SLIST_ENTRY(com_handler) link;
} com_handler_t;


void
communication_register(com_handler_t *hdler);

void
communication_init();

#endif
