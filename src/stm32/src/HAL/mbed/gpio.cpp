#include <stdlib.h>
#include <mbed.h>

extern "C" {
#include "gpio.h"
#include "debug.h"
}

struct gpio {
	PinName gpio_name;
	DigitalInOut *io;
	int reverse;
};

extern "C"  hal_gpio_t *
hal_gpio_setup(const char *gpio_name, int reverse, hal_gpio_dir_t direction)
{
	int port_num, gpio_num;
	hal_gpio_t *gpio = (hal_gpio_t *) calloc(1, sizeof(struct gpio));
	if (!gpio)
		return NULL;

	if (gpio_name[0] != 'P')
		return NULL;

	if (gpio_name[2] != '_')
		return NULL;

	port_num = gpio_name[1] - 'A';
	gpio_num = atoi(&gpio_name[3]);

	debug_puts("Opening port %d, gpio %d\n", port_num, gpio_num);

	gpio->gpio_name = (PinName) ((port_num << 4) | gpio_num);
	gpio->io = new DigitalInOut(gpio->gpio_name);
	gpio->reverse = reverse;
	
	if (direction == GPIO_DIR_OUTPUT)
		gpio->io->output();
	else
		gpio->io->input();

	return gpio;
}

extern "C" int
hal_gpio_write(hal_gpio_t *gpio, int state)
{
	gpio->io->write(state ^ gpio->reverse);
	return 0;
}

extern "C" int
hal_gpio_read(hal_gpio_t *gpio)
{
	return gpio->io->read() ^ gpio->reverse;
}