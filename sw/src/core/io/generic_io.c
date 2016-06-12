#include "generic_io.h"
#include "sensors.h"
#include "module.h"
#include "queue.h"
#include "utils.h"
#include "gpio.h"

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

/**
 * Debounce time in milliseconds
 */
#define DEBOUNCE_TIME		2

#define DEBOUNCE_SAMPLES_COUNT	8

static SLIST_HEAD( ,gen_io_ops) g_io_ops_list = SLIST_HEAD_INITIALIZER();

static SLIST_HEAD(, gen_io) g_debounced_io_list = SLIST_HEAD_INITIALIZER();

static unsigned long long g_gpio_last_read_time = 0;


static void
gen_io_poll_one(gen_io_t *gen_io)
{
	int value;

	value = gen_io_read(gen_io);

	/* Value is still different from the last one */
	if (value != gen_io->debounced_value)
		gen_io->samples++;

	/* Probably a bounce */
	if (value == gen_io->debounced_value)
		gen_io->samples = 0;

	/* We have seen enough of the value */
	if (gen_io->samples == DEBOUNCE_SAMPLES_COUNT) {
		gen_io->debounced_value = value;
		debug_puts("gen_io: %s changed: %d\r\n", gen_io->name);
		if (gen_io->cb) {
			gen_io->cb(gen_io, value, gen_io->cb_data);
		}
	}
}

static void
gen_io_main_loop()
{
	struct gen_io *gen_io;
	unsigned long long time = hal_get_micro();

	if ((time - g_gpio_last_read_time) < (DEBOUNCE_TIME * 1000))
		return;

	SLIST_FOREACH(gen_io, &g_debounced_io_list, link) {
		gen_io_poll_one(gen_io);
	}
}

void
gen_io_add_watcher(gen_io_t *gen_io, gen_io_watcher_cb cb, void *cb_data)
{
	gen_io->cb_data = cb_data;
	gen_io->cb = cb;
}

gen_io_t *
gen_io_setup(const char *name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce)
{
	gen_io_ops_t *ops;
	gen_io_t *io;
	char *prefix, *io_name;
	char name_cpy[GEN_IO_MAX_NAME_SIZE];

	debug_puts("Setting generic io for %s\r\n", name);

	PANIC_ON(direction == GPIO_DIR_OUTPUT && debounce, "Can not debounce output pin...");

	SLIST_FOREACH(ops, &g_io_ops_list, link) {
		if (strncmp(ops->prefix, name, strlen(ops->prefix)) != 0)
			continue;
		strcpy(name_cpy, name);
		
		prefix = name_cpy;
		io_name = strchr(name_cpy, '@');
		PANIC_ON(io_name == NULL, "Could not find @ separator in io name\n");

		io_name[0] = '\0';
		io_name++;

		io = malloc(sizeof(struct gen_io));
		io->io = ops->io_setup(prefix, io_name, reverse, direction, debounce);
		io->ops = ops;
		io->dir = direction;
		io->reverse = reverse;
		io->debounce = debounce;
		if (debounce)
			SLIST_INSERT_HEAD(&g_debounced_io_list, io, link);

		return io;
	}

	PANIC("Could not find io handler for io %s\r\n", name);
	return NULL;
}

void
gen_io_ops_register(gen_io_ops_t * ops)
{
	PANIC_ON(ops->io_setup == NULL || ops->prefix == NULL,
		"incomplete io operations");

	SLIST_INSERT_HEAD(&g_io_ops_list, ops, link);
}

/**
 * Module
 */
static const module_t gen_io_module = {
	.name = "gen_io",
	.main_loop = gen_io_main_loop,
	.json_parse = NULL,
};

void
gen_io_init()
{
	module_register(&gen_io_module);
}

