#ifndef _GPIO_H
#define _GPIO_H

#define GPIO_MAX_NAME_LENGTH 16

typedef struct en_gpio en_gpio_t;

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


/**
 * Create a gpio object from parameters
 * @param gpio_name GPIO name
 * @param reverse Reverse the gpio direction
 * @param direction GPIO direction (input/output)
 * @param debounce 1 if debounce needed, 0 if not
 */
en_gpio_t *
en_gpio_setup(const char *gpio_name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce);

/**
 * Set a gpio state
 * @param gpio The gpio to set value
 * @param state State to set
 */
void
en_gpio_write(en_gpio_t *gpio, int state);

/**
 * Get a gpio state
 * @param gpio The gpio to get value from
 * @return 0 gpio value
 */
int
en_gpio_read(en_gpio_t *gpio);

/**
 * Get gpio dir
 * @param gpio Gpio to get the dir from
 * @return Gpio direction
 */
gpio_dir_t
en_gpio_get_dir(en_gpio_t *gpio);

/**
 * Init GPIO subsystem
 */
void
en_gpio_init();

#endif
