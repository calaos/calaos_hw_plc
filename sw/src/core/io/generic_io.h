#ifndef _GENERIC_IO_H
#define _GENERIC_IO_H

#include <stdint.h>

#include "gpio.h"

#define GEN_IO_MAX_NAME_SIZE	16

/**
 * Prototype, public
 */

/**
 * Pin state
 */
typedef enum gpio_state {
	GPIO_STATE_LOW	= 0,
	GPIO_STATE_HIGH	= 1
} gpio_state_t;

/**
 * Pin direction
 */
typedef enum gpio_dir {
	GPIO_DIR_OUTPUT,
	GPIO_DIR_INPUT,
} gpio_dir_t;

/**
 * Gpio debouncing
 */
typedef enum gpio_debounce {
	GPIO_DEBOUNCE_DISABLE = 0,
	GPIO_DEBOUNCE_ENABLE = 1,
} gpio_debounce_t;


typedef struct gen_io gen_io_t;

gen_io_t *
gen_io_setup(const char *name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce);


typedef struct gen_io_ops {
	void (*io_write)(void *io, int state);
	void (*io_set_dir)(void *io, gpio_dir_t dir);
	int (*io_read)(void *io);
	void * (*io_setup)(const char *io_name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce);
	const char *prefix;
} gen_io_ops_t;

void
gen_io_ops_register(const gen_io_ops_t * ops);


/**
 * Implementation, private
 */
struct gen_io {
	const gen_io_ops_t *ops;
	void *io;
	gpio_dir_t dir;
	uint8_t reverse;
};


static inline void
gen_io_write(gen_io_t *io, int state)
{
	io->ops->io_write(io->io, (state & 0x1) ^ io->reverse);
}

static inline int
gen_io_read(gen_io_t *io)
{
	return io->ops->io_read(io->io) ^ io->reverse;
}

static inline gpio_dir_t
gen_io_get_dir(gen_io_t *io)
{
	return io->dir;
}

void
gen_io_set_dir(gen_io_t *io, gpio_dir_t dir)
{
	io->ops->io_set_dir(io->io, dir);
}



#endif
