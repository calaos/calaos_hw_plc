#ifndef _PINS_H
#define _PINS_H

/**
 * PIN stuff
 */

typedef struct pin pin_t;

/**
 * Pin state
 */
typedef enum pin_state {
	PIN_STATE_LOW	= 0,
	PIN_STATE_HIGH	= 1
} pin_state_t;

/**
 * Pin direction
 */
typedef enum pin_dir {
	PIN_DIR_OUTPUT,
	PIN_DIR_INPUT,
} pin_dir_t;

/**
 * Create a pin object from parameters
 */
pin_t *
pin_setup(const char *pin_name, int reverse, pin_dir_t direction);

/**
 * 
 */
int
pin_set_state(pin_t *pin, int state);

/**
 * 
 */
int
pin_get_state(pin_t *pin);

#endif
