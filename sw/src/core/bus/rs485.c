#define _GNU_SOURCE 1

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "HAL.h"
#include "utils.h"
#include "debug.h"
#include "config.h"
#include "module.h"
#include "rs485.h"

#define DEFAULT_BAUDRATE	115200

typedef struct rs485_bus {
	char *name;
	hal_uart_t *uart;
	gen_io_t *de;
	SLIST_ENTRY(rs485_bus) link;
} rs485_bus_t;

SLIST_HEAD(, rs485_bus) g_rs485_bus_list = SLIST_HEAD_INITIALIZER(g_rs485_bus_list);


static int
rs485_bus_write(rs485_bus_t *rs, const uint8_t *data, unsigned int length)
{
	/* Set Data Enable high to drive the line */
	gen_io_write(rs->de, 1);
	hal_uart_write(rs->uart, data, length);
	/* Then set it low to receive data on uart */
	gen_io_write(rs->de, 0);

	return 0;
}

static int
rs485_bus_read(rs485_bus_t *rs, const uint8_t *data, unsigned int *ret_len)
{
	int ret_len

	hal_uart_write(rs->uart, data, length *ret_len);
}

static int
rs485_json_parse_one(json_value* sensor)
{
	int length, i;
	json_value *value;
	rs485_bus_t *rs;
	const char *name;
	const char *tx = NULL, *rx = NULL;
	unsigned int baudrate = DEFAULT_BAUDRATE;

        rs = calloc(1, sizeof(struct rs485_bus));
        PANIC_ON(!rs, "Failed to alloc rs485 bus");

        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			rs->name = strdup(value->u.string.ptr);
		} else if (strcmp(name, "de") == 0) {
			rs->de = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "tx") == 0) {
			tx = value->u.string.ptr;
		} else if (strcmp(name, "rx") == 0) {
			rx = value->u.string.ptr;
		} else if (strcmp(name, "baudrate") == 0) {
			baudrate = value->u.integer;
		} 
        }

        PANIC_ON(rx == NULL || tx == NULL || rs->de == NULL, "Missing parameters for rs485 bus");

	rs->uart = hal_uart_setup(tx, rx, baudrate);
	PANIC_ON(rs->uart == NULL, "Failed to create uart for rs485 bus");

	gen_io_write(rs->de, 0);

	dbg_log("Adding rs485 bus %s with %d baudrate\n", rs->name, baudrate);
	SLIST_INSERT_HEAD(&g_rs485_bus_list, rs, link);

	return 0;
}

static int
rs485_json_parse(json_value* section)
{
        unsigned int i;

	for (i = 0; i < section->u.array.length; i++) {
		rs485_json_parse_one(section->u.array.values[i]);
	}
	return 0;
}


/**
 * Module
 */
static const module_t rs485_module = {
	.name = "rs485",
	.json_parse = rs485_json_parse,
};

void
rs485_init()
{
	module_register(&rs485_module);
}


