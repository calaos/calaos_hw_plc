#define _GNU_SOURCE 1

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

/**
 * List of debounced IOs
 */
static SLIST_HEAD(, gen_io) g_debounced_io_list = SLIST_HEAD_INITIALIZER();

/**
 * List of IOs
 */
static SLIST_HEAD(, gen_io) g_gen_io_list = SLIST_HEAD_INITIALIZER();

static unsigned long long g_gpio_last_read_time = 0;

static void
gen_io_poll_one(gen_io_t *gen_io)
{
	int value;

	value = gen_io->ops->io_read(gen_io->io);

	/* Value is still different from the last one */
	if (value != gen_io->debounced_value)
		gen_io->samples++;

	/* Probably a bounce */
	if (value == gen_io->debounced_value)
		gen_io->samples = 0;

	/* We have seen enough of the value */
	if (gen_io->samples == DEBOUNCE_SAMPLES_COUNT) {
		gen_io->debounced_value = value;

		dbg_log("gen_io: %s changed: %d\n", gen_io->name, value);
		if (gen_io->cb) {
			gen_io->cb(gen_io, value ^ gen_io->reverse, gen_io->cb_data);
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

	g_gpio_last_read_time = time;

	SLIST_FOREACH(gen_io, &g_debounced_io_list, deb_link) {
		gen_io_poll_one(gen_io);
	}
}

void
gen_io_add_watcher(gen_io_t *gen_io, gen_io_watcher_cb cb, void *cb_data)
{
	gen_io->cb_data = cb_data;
	gen_io->cb = cb;
}

static gen_io_t *
gen_io_get_by_name(const char *name)
{
	struct gen_io *gen_io;

	SLIST_FOREACH(gen_io, &g_gen_io_list, link) {
		if (strcmp(name, gen_io->name) == 0) {
			return gen_io;
		}
	}
	
	return NULL;
}


gen_io_t *
gen_io_setup(const char *name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce, gpio_pin_mode_t mode)
{
	gen_io_ops_t *ops;
	gen_io_t *io;
	char *prefix, *io_name;
	char name_cpy[GEN_IO_MAX_NAME_SIZE];

	dbg_log("Setting generic io for %s\n", name);

	PANIC_ON(direction == GPIO_DIR_OUTPUT && debounce, "Can not debounce output pin...");
	
	io = gen_io_get_by_name(name);
	if (io) {
		PANIC_ON(io->dir != direction || io->debounce != debounce || io->reverse != reverse,
			"IO required already setup with different parameters");

		dbg_log("Retrieving already existing io %s\n", name);
		return io;
	}

	SLIST_FOREACH(ops, &g_io_ops_list, link) {
		if (strncmp(ops->prefix, name, strlen(ops->prefix)) != 0)
			continue;

		strcpy(name_cpy, name);

		prefix = name_cpy;
		io_name = strchr(name_cpy, '@');
		PANIC_ON(io_name == NULL, "Could not find @ separator in io name\n");

		io_name[0] = '\0';
		io_name++;

		io = calloc(1, sizeof(struct gen_io));
		PANIC_ON(!io, "Failed to allocate data");

		io->io = ops->io_setup(prefix, io_name, reverse, direction, debounce, mode);
		io->ops = ops;
		io->dir = direction;
		io->reverse = reverse;
		io->debounce = debounce;
		io->name = strdup(name);

		if (io->dir == GPIO_DIR_OUTPUT)
			gen_io_write(io, 0);

		SLIST_INSERT_HEAD(&g_gen_io_list, io, link);
		
		if (debounce)
			SLIST_INSERT_HEAD(&g_debounced_io_list, io, deb_link);

		return io;
	}

	PANIC("Could not find io handler for io %s\n", name);
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
	g_gpio_last_read_time = hal_get_micro();
	module_register(&gen_io_module);
}

