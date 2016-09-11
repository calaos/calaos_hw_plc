#define _GNU_SOURCE 1

#include "shift_register.h"
#include "generic_io.h"
#include "sensors.h"
#include "module.h"
#include "debug.h"
#include "utils.h"
#include "queue.h"
#include "json.h"

#include <string.h>
#include <stdlib.h>

struct shift_register {
	char *name;		/* Shift register name */
	gen_io_t *data;
	gen_io_t *latch;
	gen_io_t *clock;
	uint32_t current_value;
	uint8_t count;		/* Count of output for this shift register */
	SLIST_ENTRY(shift_register) link;
};

struct shift_register_io {
	struct shift_register *sr;
	int output;
};

typedef struct shift_register shift_register_t;
typedef struct shift_register_io shift_register_io_t;

static SLIST_HEAD(,shift_register) g_shift_registers = SLIST_HEAD_INITIALIZER();

shift_register_t *
shift_register_get_by_name(const char *name) 
{
	struct shift_register *sr;
	
	SLIST_FOREACH(sr, &g_shift_registers, link) {
		if (strncmp(name, sr->name, strlen(name)) == 0)
			return sr;
	}

	return NULL;
}

static int
shift_register_json_parse_one(json_value* sensor)
{
	int length, i;
	json_value *value;
	shift_register_t *sr;
	const char *name;

        sr = calloc(1, sizeof(struct shift_register));
        PANIC_ON(!sr, "Failed to alloc shift register");

        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			sr->name = strdup(value->u.string.ptr);
		} else if (strcmp(name, "data") == 0) {
			sr->data = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "latch") == 0) {
			sr->latch = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "clock") == 0) {
			sr->clock = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "count") == 0) {
			sr->count = value->u.integer;
		}
        }

	dbg_log("Adding shift register %s with %d output\n", sr->name, sr->count);
	SLIST_INSERT_HEAD(&g_shift_registers, sr, link);

	return 0;
}


static int
shift_register_json_parse(json_value* section)
{
        unsigned int i;

	for (i = 0; i < section->u.array.length; i++) {
		shift_register_json_parse_one(section->u.array.values[i]);
	}
	return 0;
}


static void
shift_register_update(shift_register_t *sr)
{
	int i;

	for (i = sr->count; i >= 0; i--) {
		gen_io_write(sr->clock, 0);
		gen_io_write(sr->data, (sr->current_value >> i) & 0x1);
		gen_io_write(sr->clock, 1);
	}
	gen_io_write(sr->clock, 0);

	/* Unleash the beast ! */
	gen_io_write(sr->latch, 1);
	gen_io_write(sr->latch, 0);
}

static int
shift_register_set_output(shift_register_t *sr, int output, int state)
{
	dbg_log("Setting shift register ouput %d to value %d\n", output, state);

	if (state == 0)
		sr->current_value &= ~(1 << output);
	else
		sr->current_value |= (1 << output);

	shift_register_update(sr);
	
	return 0;
}

static void *
shift_register_io_setup(const char *prefix, const char *srio_name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce, gpio_pin_mode_t mode)
{
	shift_register_io_t *srio = calloc(1, sizeof(shift_register_io_t));
	if (!srio)
		return NULL;

	dbg_log("Setup shift register io %s, reverse: %d, dir: %d, debounce: %d\n",
			srio_name, reverse, direction, debounce);

	srio->output = atoi(srio_name);
	srio->sr = shift_register_get_by_name(prefix);
	PANIC_ON(srio->sr == NULL, "Failed to get shift register %s\n", prefix);

	return srio;
}

static void
shift_register_io_write(void *io, int state)
{
	shift_register_io_t *sr_io = io;
	shift_register_set_output(sr_io->sr, sr_io->output, state);
}

static int
shift_register_io_read(void *io)
{
	shift_register_io_t *sr_io = io;
	shift_register_t *sr = sr_io->sr;

	return (sr->current_value >> sr_io->output) & 0x1;
}

/**
 * Module
 */
static const module_t shift_register_module = {
	.name = "shift_registers",
	.main_loop = NULL,
	.json_parse = shift_register_json_parse,
};

static gen_io_ops_t shift_register_io_ops = {
	.io_write = shift_register_io_write,
	.io_read = shift_register_io_read,
	.io_setup = shift_register_io_setup,
	.prefix = "sr",
};

void
shift_register_init()
{
	gen_io_ops_register(&shift_register_io_ops);
	module_register(&shift_register_module);
}
