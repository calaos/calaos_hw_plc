#include "HAL.h"
#include "gpio.h"
#include "utils.h"
#include "queue.h"
#include "module.h"

#include <stdlib.h>
#include <string.h>

#define GPIO_PREFIX	"gpio"
#define GPIO_PREFIX_SEPARATOR	"@"

/**
 * Debounce time in milliseconds
 */
#define DEBOUNCE_TIME		2

#define DEBOUNCE_SAMPLES_COUNT	8

struct en_gpio {
	hal_gpio_t *hal_gpio;
	gpio_debounce_t debounce;
	char debounced_value, samples;
	SLIST_ENTRY(en_gpio) link;
};

typedef struct en_gpio en_gpio_t;

SLIST_HEAD( ,en_gpio) g_debounce_gpios = SLIST_HEAD_INITIALIZER();

void *
en_gpio_setup(const char *gpio_name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce)
{
	en_gpio_t *gpio = calloc(1, sizeof(struct en_gpio));
	if (!gpio)
		return NULL;

	debug_puts("Setup gpio %s, reverse: %d, dir: %d, debounce: %d\r\n",
			gpio_name, reverse, direction, debounce);

	gpio->debounce = debounce;
	gpio->debounced_value = 0;
	gpio->hal_gpio = hal_gpio_setup(gpio_name + strlen(GPIO_PREFIX) + strlen(GPIO_PREFIX_SEPARATOR), reverse, direction);

	if (direction == GPIO_DIR_INPUT && debounce)
		SLIST_INSERT_HEAD(&g_debounce_gpios, gpio, link);

	debug_puts("GPIO address %p\r\n", gpio);
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

	if (gpio->debounce)
		return gpio->debounced_value;
	else
		return hal_gpio_read(gpio->hal_gpio);
}


void
en_gpio_set_dir(void *io, gpio_dir_t dir)
{
	en_gpio_t *gpio = io;

	hal_gpio_set_dir(gpio->hal_gpio, dir);
}

static unsigned long long g_gpio_last_read_time = 0;

static void
en_gpio_main_loop()
{
	unsigned long long time = hal_get_micro();
	en_gpio_t *gpio;
	
	if ((time - g_gpio_last_read_time) < (DEBOUNCE_TIME * 1000))
		return;

	g_gpio_last_read_time = time;
	SLIST_FOREACH(gpio, &g_debounce_gpios, link) {
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

static const module_t en_gpio_module = {
	.name = "en_gpio",
	.main_loop = en_gpio_main_loop,
	.json_parse = NULL,
};

static const gen_io_ops_t gpio_ops = {
	.io_write = en_gpio_write,
	.io_read = en_gpio_read,
	.io_set_dir = en_gpio_set_dir,
	.io_setup = en_gpio_setup,
	.prefix = GPIO_PREFIX,
};

void
en_gpio_init()
{
	g_gpio_last_read_time = hal_get_micro();

	gen_io_ops_register(&gpio_ops);
	module_register(&en_gpio_module);
}
