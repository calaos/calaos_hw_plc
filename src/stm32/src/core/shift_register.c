#include "shift_register.h"
#include "sensors.h"
#include "module.h"
#include "debug.h"
#include "generic_io.h"
#include "json.h"

#include <string.h>

#define MAX_SHIFT_REGISTERS	4	

struct shift_register {
	char *name;		/* Shift register name */
	char count;		/* Count of output for this shift register */
	gen_io_t *data;
	gen_io_t *latch;
	gen_io_t *clock;
	uint64_t current_value;
};

struct shift_register_io {
	struct shift_register *sr;
	int output;
};

typedef struct shift_register shift_register_t;
typedef struct shift_register_io shift_register_io_t;

static int g_max_shift_register_id = 0;
static struct shift_register *g_shift_registers[MAX_SHIFT_REGISTERS];

shift_register_t *
shift_register_get_by_name(const char *name) 
{
	int i;

	for (i = 0; i < g_max_shift_register_id; i++) {
		if (strncmp(name, g_shift_registers[i]->name, strlen(name)) == 0)
			return g_shift_registers[i];
	}
	
	return NULL;
}

static int
sensors_json_parse_sensor(json_value* sensor)
{
	int length, i;
	json_value *value;
	shift_register_t *sr;
	const char *name;

        sr = calloc(1, sizeof(struct shift_register));

        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			sr->name = strdup(value->u.string.ptr);
		} else if (strcmp(name, "data") == 0) {
			sr->data = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "latch") == 0) {
			sr->latch = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "clock") == 0) {
			sr->clock = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "count") == 0) {
			sr->count = value->u.integer;
		}
        }

	debug_puts("Adding shift register %s\r\n", sr->name);
	g_shift_registers[g_max_shift_register_id++] = sr;

	return 0;
}


static int
shift_register_json_parse(json_value* value)
{
        unsigned int length, i, j;
	json_value *entry;

	if (value == NULL || value->type != json_object) {
                return -1;
        }

        length = value->u.object.length;
        for (i = 0; i < length; i++) {
		/* We only care about sensor section*/
		if (strcmp(value->u.object.values[i].name, "shift_registers") == 0) {
			debug_puts("Found shift register section\r\n");
			entry = value->u.object.values[i].value;
			for (j = 0; j < entry->u.array.length; j++) {
				sensors_json_parse_sensor(entry->u.array.values[j]);
			}

			return 0;
		}
        }

        return -1;
}


static void
shift_register_set_state(shift_register_t *sr, uint64_t value)
{
	int i;

	for (i = 0; i < sr->count; i++) {
		gen_io_write(sr->data, value & (1 << i));
		gen_io_write(sr->clock, 1);
		gen_io_write(sr->clock, 0);
	}

	/* Unleash the beast ! */
	gen_io_write(sr->latch, 1);
	gen_io_write(sr->latch, 0);
}

static int
shift_register_set_output(shift_register_t *sr, int output, gpio_state_t state)
{
	debug_puts("Setting shift register ouput %d to value %d\r\n", output, state);

	if (state == 0)
		sr->current_value &= ~(1 << output);
	else
		sr->current_value |= (1 << output);

	shift_register_set_state(sr, sr->current_value);
	
	return 0;
}

void *
shift_register_io_setup(const char *srio_name, int reverse, gpio_dir_t direction, gpio_debounce_t debounce)
{
	char name_cpy[GEN_IO_MAX_NAME_SIZE];
	char *sep;

	shift_register_io_t *srio = calloc(1, sizeof(shift_register_io_t));
	if (!srio)
		return NULL;
	strcpy(name_cpy, srio_name);
	debug_puts("Setup shift register io %s, reverse: %d, dir: %d, debounce: %d\r\n",
			srio_name, reverse, direction, debounce);
	/* FIXME: better error handling */
	sep = strchr(srio_name, '@');
	sep[0] = '\0';
	srio->output = atoi(sep + 1);
	srio->sr = shift_register_get_by_name(name_cpy);

	return srio;
}

void shift_register_io_write(void *io, gpio_state_t state)
{
	shift_register_io_t *sr_io = io;
	shift_register_set_output(sr_io->sr, sr_io->output, state);
}	

/**
 * Module
 */
static const module_t shift_register_module = {
	.name = "shift_register",
	.main_loop = NULL,
	.json_parse = shift_register_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};

static const gen_io_ops_t shift_register_io_ops = {
	.io_write = shift_register_io_write,
	.io_read = NULL,
	.io_setup = shift_register_io_setup,
	.prefix = "sr",
};

void
shift_register_init()
{
	gen_io_ops_register(&shift_register_io_ops);
	module_register(&shift_register_module);
}
