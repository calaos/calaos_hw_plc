#ifndef _PINS_H
#define _PINS_H

/**
 * PIN stuff
 */

typedef struct gpio hal_gpio_t;

/**
 * Pin state
 */
typedef enum hal_gpio_state {
	GPIO_STATE_LOW	= 0,
	GPIO_STATE_HIGH	= 1
} hal_gpio_state_t;

/**
 * Pin direction
 */
typedef enum hal_gpio_dir {
	GPIO_DIR_OUTPUT,
	GPIO_DIR_INPUT,
} hal_gpio_dir_t;

/**
 * Create a gpio object from parameters
 * @param gpio_name GPIO name
 * @param reverse Reverse the gpio direction
 * @param direction GPIO direction (input/output)
 */
hal_gpio_t *
hal_gpio_setup(const char *gpio_name, int reverse, hal_gpio_dir_t direction);

/**
 * Set a gpio state
 * @param gpio The gpio to set value
 * @param state State to set
 * @return 0 on success, a positive value on error
 */
int
hal_gpio_write(hal_gpio_t *gpio, int state);

/**
 * Get a gpio state
 * @param gpio The gpio to get value from
 * @return 0 on success, a positive value on error
 */
int
hal_gpio_read(hal_gpio_t *gpio);

/**
 * Get gpio dir
 * @param gpio Gpio to get the dir from
 * @return Gpio direction
 */
hal_gpio_dir_t
hal_gpio_get_dir(hal_gpio_t *gpio);


#endif
