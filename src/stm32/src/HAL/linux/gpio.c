#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "utils.h"
#include "HAL.h"

struct hal_gpio {
	int gpio_num;
};

hal_gpio_t *
hal_gpio_setup(const char *gpio_name, int reverse, gpio_dir_t direction)
{
	hal_gpio_t *gpio = calloc(1, sizeof(struct hal_gpio));
	if (!gpio)
		return NULL;

	debug_puts("Creating linux gpio %s, reverse: %d, direction: %d\n", gpio_name, reverse, direction);
	gpio->gpio_num = atoi(gpio_name);

	return gpio;

}

void
hal_gpio_write(__unused__ hal_gpio_t *gpio, __unused__ int state)
{
}

int
hal_gpio_read(hal_gpio_t *gpio)
{
	gpio = gpio;
	return 0;
}
