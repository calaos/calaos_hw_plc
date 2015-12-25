#include "HAL.h"
#include "gpio.h"
#include "utils.h"
#include "module.h"

#include <stdlib.h>

/**
 * Debounce time in milliseconds
 */
#define DEBOUNCE_TIME		2

#define DEBOUNCE_SAMPLES_COUNT	8 

#define MAX_OPENED_GPIOS	64

struct en_gpio {
	hal_gpio_t *hal_gpio;
	gpio_dir_t dir;
	gpio_debounce_t debounce;
	char debounced_value, samples;
};

/**
 * Currently opened GPIOs
 */
static struct en_gpio *g_debounce_gpios[MAX_OPENED_GPIOS];
static unsigned int g_gpio_count = 0;

en_gpio_t *
en_gpio_setup(const char *gpio_name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce)
{
	en_gpio_t *gpio = calloc(1, sizeof(struct en_gpio));
	if (!gpio)
		return NULL;
		
	debug_puts("Setup gpio %s, reverse: %d, dir: %d, debounce: %d\r\n",
			gpio_name, reverse, direction, debounce);
	
	gpio->dir = direction;
	gpio->debounce = debounce;
	gpio->debounced_value = 0;
	gpio->hal_gpio = hal_gpio_setup(gpio_name, reverse, direction);
	
	if (direction == GPIO_DIR_INPUT && debounce)
		g_debounce_gpios[g_gpio_count++] = gpio;

	debug_puts("GPIO address %p\r\n", gpio);
	return gpio;
}

void
en_gpio_write(en_gpio_t *gpio, int state)
{
	if (gpio->dir != GPIO_DIR_OUTPUT)
		PANIC("Calling gpio write on input gpio");

	hal_gpio_write(gpio->hal_gpio, state);
}

int
en_gpio_read(en_gpio_t *gpio)
{
	if (gpio->dir != GPIO_DIR_INPUT)
		PANIC("Calling gpio read on output gpio");

	if (gpio->debounce)
		return gpio->debounced_value;
	else
		return hal_gpio_read(gpio->hal_gpio);
}

gpio_dir_t
en_gpio_get_dir(en_gpio_t *gpio)
{
	return gpio->dir;
}

static unsigned long long g_gpio_last_read_time = 0;

static void
en_gpio_main_loop()
{
	unsigned long long time = hal_get_micro();
	unsigned int i;
	en_gpio_t *gpio;
	
	if ((time - g_gpio_last_read_time) * 1000 < DEBOUNCE_TIME)
		return;

	g_gpio_last_read_time = time;
	for(i = 0; i < g_gpio_count; i++) {
		gpio = g_debounce_gpios[i];
		char value = hal_gpio_read(gpio->hal_gpio);

		/* Value is still different from the last one */
		if (value != gpio->debounced_value)
			gpio->samples++;
		/* Probably a bounce */
		if (value == gpio->debounced_value)
			gpio->samples = 0;
		
		/* We have seen enough of the value */
		if (gpio->samples == DEBOUNCE_SAMPLES_COUNT)
			gpio->debounced_value = value;
	}
	
}

const module_t en_gpio_module = {
	.name = "en_gpio",
	.main_loop = en_gpio_main_loop,
	.json_parse = NULL,
};

void
en_gpio_init()
{
	g_gpio_last_read_time = hal_get_micro();
	module_register(&en_gpio_module);
}
