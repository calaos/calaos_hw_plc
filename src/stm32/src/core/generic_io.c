#include "shift_register.h"
#include "generic_io.h"
#include "utils.h"
#include "gpio.h"

#include <string.h>
#include <stdlib.h>

#define MAX_GENERIC_IO_OPS	3

struct gen_io {
	const gen_io_ops_t *ops;
	void *io;
	gpio_dir_t dir;
};

static unsigned int g_gen_io_ops_count = 0;
static const gen_io_ops_t *g_gen_io_ops[MAX_GENERIC_IO_OPS];

gen_io_t *
gen_io_setup(const char *name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce)
{
	unsigned int i;
	const gen_io_ops_t *ops;
	gen_io_t *io;
	
	for (i = 0; i < g_gen_io_ops_count; i++) {
		ops = g_gen_io_ops[i];
		if (strncmp(ops->prefix, name, strlen(ops->prefix)) == 0) {
			io = malloc(sizeof(struct gen_io));
			io->io = ops->io_setup(name + strlen(ops->prefix), reverse, direction, debounce);
			io->ops = ops;
			io->dir = direction;
			return io;
		}
	}

	return NULL;
}

void
gen_io_ops_register(const gen_io_ops_t * ops)
{
	g_gen_io_ops[g_gen_io_ops_count++] = ops;
}

void
gen_io_write(gen_io_t *io, gpio_state_t state)
{
	if (io->dir == GPIO_DIR_INPUT)
		PANIC("Write called on input GPIO");
	io->ops->io_write(io->io, state);
}

gpio_state_t
gen_io_read(gen_io_t *io)
{
	if (io->dir == GPIO_DIR_OUTPUT)
		PANIC("Read called on output GPIO");

	return io->ops->io_read(io->io);
}

gpio_dir_t
gen_io_get_dir(gen_io_t *io)
{
	return io->dir;
}
