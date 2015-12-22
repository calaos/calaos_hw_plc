#ifndef _GPIO_H
#define _GPIO_H

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


#endif
