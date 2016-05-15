#include "shift_register.h"
#include "generic_io.h"
#include "utils.h"
#include "gpio.h"

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

#define MAX_GENERIC_IO_OPS	3

static unsigned int g_gen_io_ops_count = 0;
static const gen_io_ops_t *g_gen_io_ops[MAX_GENERIC_IO_OPS];

gen_io_t *
gen_io_setup(const char *name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce)
{
	unsigned int i;
	const gen_io_ops_t *ops;
	gen_io_t *io;
	
	debug_puts("Setting generic io for %s\r\n", name);
	
	for (i = 0; i < g_gen_io_ops_count; i++) {
		ops = g_gen_io_ops[i];
		if (strncmp(ops->prefix, name, strlen(ops->prefix)) == 0) {
			io = malloc(sizeof(struct gen_io));
			io->io = ops->io_setup(name, reverse, direction, debounce);
			io->ops = ops;
			io->dir = direction;
			io->reverse = reverse;
			return io;
		}
	}

	PANIC("Could not find io handler for io %s\r\n", name);
	return NULL;
}

void
gen_io_ops_register(const gen_io_ops_t * ops)
{
	PANIC_ON(ops->io_setup == NULL || ops->prefix == NULL,
		"incomplete io operations");

        PANIC_ON(g_gen_io_ops_count == MAX_GENERIC_IO_OPS, "Too many generic io ops\r\n");

	g_gen_io_ops[g_gen_io_ops_count++] = ops;
}
