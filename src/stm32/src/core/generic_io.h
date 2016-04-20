#ifndef _GENERIC_IO_H
#define _GENERIC_IO_H

#include "gpio.h"

#define GEN_IO_MAX_NAME_SIZE	16

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
	void (*io_write)(void *io, gpio_state_t state);
	gpio_state_t (*io_read)(void *io);
	void * (*io_setup)(const char *io_name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce);
	const char *prefix;
} gen_io_ops_t;

void
gen_io_ops_register(const gen_io_ops_t * ops);

void
gen_io_write(gen_io_t *io, int state);

gpio_state_t
gen_io_read(gen_io_t *io);


gpio_dir_t
gen_io_get_dir(gen_io_t *io);



#endif
