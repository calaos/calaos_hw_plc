#include <stdlib.h>
#include <mbed.h>
#include "mbed_util.h"

extern "C" {
#include "HAL.h"
#include "debug.h"
}

struct hal_gpio {
	PinName gpio_name;
	DigitalInOut *io;
};

extern "C"  hal_gpio_t *
hal_gpio_setup(const char *gpio_name, int reverse, gpio_dir_t direction)
{
	hal_gpio_t *gpio = (hal_gpio_t *) calloc(1, sizeof(struct hal_gpio));
	if (!gpio)
		return NULL;

	gpio->gpio_name = mbed_pinname_from_str(gpio_name);
	if(gpio->gpio_name == NC)
		return NULL;
	
	if (direction == GPIO_DIR_OUTPUT) {
		gpio->io = new DigitalInOut(gpio->gpio_name, PIN_OUTPUT, PullNone, 0 ^ reverse);
	} else {
		gpio->io = new DigitalInOut(gpio->gpio_name, PIN_INPUT, PullNone, 0);
	}

	return gpio;
}

extern "C" void
hal_gpio_write(hal_gpio_t *gpio, int state)
{
	gpio->io->write(state);
}

extern "C" int
hal_gpio_read(hal_gpio_t *gpio)
{
	return gpio->io->read();
}

extern "C" void
hal_gpio_set_dir(hal_gpio_t *gpio, gpio_dir_t dir)
{
	if (dir == GPIO_DIR_INPUT)
		gpio->io->input();
	else
		gpio->io->output();	
}
