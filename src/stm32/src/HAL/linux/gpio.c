#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "gpio.h"

struct gpio {
	int gpio_num;
	int reverse;
	hal_gpio_dir_t direction;
};

hal_gpio_t *
hal_gpio_setup(const char *gpio_name, int reverse, hal_gpio_dir_t direction)
{
	hal_gpio_t *gpio = calloc(1, sizeof(struct gpio));
	if (!gpio)
		return NULL;

	debug_puts("Creating gpio %s, reverse: %d, direction: %d\n", gpio_name, reverse, direction);
	gpio->gpio_num = atoi(gpio_name);
	gpio->reverse = reverse;
	gpio->direction = direction;


	return gpio;

}

int
hal_gpio_write(hal_gpio_t *gpio, int state)
{
	debug_puts("[PIN] gpio %d set to %d\n", gpio->gpio_num, state);
	return 0;
}

int
hal_gpio_read(hal_gpio_t *gpio)
{
	gpio = gpio;
	return 0;
}

hal_gpio_dir_t
hal_gpio_get_dir(hal_gpio_t *gpio)
{
	return gpio->direction;
}
