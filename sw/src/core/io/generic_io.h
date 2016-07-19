#ifndef _GENERIC_IO_H
#define _GENERIC_IO_H

#include <stdint.h>

#include "queue.h"
#include "gpio.h"

#define GEN_IO_MAX_NAME_SIZE	16

/**
 * Prototype, public
 */

void
gen_io_init();

/**
 * Pin state
 */
typedef enum gpio_state {
	GPIO_STATE_LOW	= 0,
	GPIO_STATE_HIGH	= 1
} gpio_state_t;

/**
 * GPIO pull up state
 */
typedef enum gpio_pin_mode {
	GPIO_MODE_PULL_NONE = 0,
	GPIO_MODE_PULL_DOWN,
	GPIO_MODE_PULL_UP,
	GPIO_MODE_OPEN_DRAIN,
} gpio_pin_mode_t;

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

/**
 * Setup a new generic io
 * @param name IO name
 * @param reverse 1 if the IO is reversed, 0 if not
 * @param direction IO direction
 * @param debounce 1 to debounce input, 0 if not
 */
gen_io_t *
gen_io_setup(const char *name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce, gpio_pin_mode_t pull);

/**
 * Watcher callback when io status changes
 * @param io The 
 */
typedef void (*gen_io_watcher_cb)(gen_io_t *io, int value, void * data);

/**
 * Add a watcher for an IO
 * @param gen_io generic IO to watch
 * @param cb Status update callback
 * @param data Specific data for the callback
 */
void
gen_io_add_watcher(gen_io_t *gen_io, gen_io_watcher_cb cb, void *data);

/**
 * Generic IO operations
 */
typedef struct gen_io_ops {
	void (*io_write)(void *io, int state);
	void (*io_set_dir)(void *io, gpio_dir_t dir);
	int (*io_read)(void *io);
	void * (*io_setup)(const char *prefix, const char *io_name, int reverse,
		gpio_dir_t direction, gpio_debounce_t debounce, gpio_pin_mode_t mode);
	const char *prefix;

	/* Private */
	SLIST_ENTRY(gen_io_ops) link;
} gen_io_ops_t;

/**
 * Register specific IO operations
 * @param ops IO operations
 */
void
gen_io_ops_register(gen_io_ops_t * ops);

/**
 * Implementation, private
 */
struct gen_io {
	const gen_io_ops_t *ops;
	void *io;
	gpio_dir_t dir;
	uint8_t reverse;
	uint8_t debounce;
	uint8_t debounced_value, samples;
	/* watcher part */
	gen_io_watcher_cb cb;
	void *cb_data;

	/* Debug */
	char *name;

	/* Private */
	SLIST_ENTRY(gen_io) deb_link;
	SLIST_ENTRY(gen_io) link;
};

static inline void
gen_io_write(gen_io_t *io, int state)
{
	io->ops->io_write(io->io, (state & 0x1) ^ io->reverse);
}

static inline int
gen_io_read(gen_io_t *io)
{
	if (io->debounce)
		return io->debounced_value ^ io->reverse;
	else
		return io->ops->io_read(io->io) ^ io->reverse;
}

static inline gpio_dir_t
gen_io_get_dir(gen_io_t *io)
{
	return io->dir;
}

static inline void
gen_io_set_dir(gen_io_t *io, gpio_dir_t dir)
{
	io->ops->io_set_dir(io->io, dir);
}



#endif
