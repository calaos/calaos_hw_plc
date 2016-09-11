#include "HAL.h"
#include "gpio.h"
#include "utils.h"
#include "queue.h"
#include "module.h"

#include <stdlib.h>
#include <string.h>

#define GPIO_PREFIX	"gpio"


struct en_gpio {
	hal_gpio_t *hal_gpio;
};

typedef struct en_gpio en_gpio_t;

void *
en_gpio_setup(const char *prefix, const char *gpio_name, int reverse,
		gpio_dir_t direction, gpio_debounce_t debounce, gpio_pin_mode_t mode)
{
	en_gpio_t *gpio = calloc(1, sizeof(struct en_gpio));
	if (!gpio)
		return NULL;

	dbg_log("Setup gpio %s, reverse: %d, dir: %d, debounce: %d\n",
			gpio_name, reverse, direction, debounce);

	gpio->hal_gpio = hal_gpio_setup(gpio_name, reverse, direction, mode);

	dbg_log("GPIO address %p\n", gpio);
	return gpio;
}

void
en_gpio_write(void *io, int state)
{
	en_gpio_t *gpio = io;

	hal_gpio_write(gpio->hal_gpio, state);
}

int
en_gpio_read(void *io)
{
	en_gpio_t *gpio = io;

	return hal_gpio_read(gpio->hal_gpio);
}

void
en_gpio_set_dir(void *io, gpio_dir_t dir)
{
	en_gpio_t *gpio = io;

	hal_gpio_set_dir(gpio->hal_gpio, dir);
}

static gen_io_ops_t gpio_ops = {
	.io_write = en_gpio_write,
	.io_read = en_gpio_read,
	.io_set_dir = en_gpio_set_dir,
	.io_setup = en_gpio_setup,
	.prefix = GPIO_PREFIX,
};

void
en_gpio_init()
{
	gen_io_ops_register(&gpio_ops);
}
