#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "json.h"
#include "queue.h"

#define DEFAULT_BAUDRATE	115200

void
std_puts(const char *format, ...);

void
dbg_puts(const char *format, ...);

typedef struct com_handler {
	/**
	 * Output a standard string
	 */
	void (*put_std_str)(const char *str);
	/**
	 * Output a debug string
	 */
	void (*put_dbg_str)(const char *str);
	
	SLIST_ENTRY(com_handler) link;
} com_handler_t;


void
communication_register(com_handler_t *hdler);

void
communication_init();

#endif
