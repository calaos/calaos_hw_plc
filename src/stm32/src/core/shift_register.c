#include "shift_register.h"
#include "sensors.h"
#include "module.h"
#include "debug.h"
#include "gpio.h"
#include "json.h"

#include <string.h>

#define MAX_SHIFT_REGISTERS	4	

struct shift_register {
	char *name;		/* Shift register name */
	char count;		/* Count of output for this shift register */
	en_gpio_t *data;
	en_gpio_t *latch;
	en_gpio_t *clock;
	uint64_t current_value;
};

static int g_max_shift_register_id = 0;
static struct shift_register *g_shift_registers[MAX_SHIFT_REGISTERS];

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
			sr->data = en_gpio_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "latch") == 0) {
			sr->latch = en_gpio_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "clock") == 0) {
			sr->clock = en_gpio_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
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


static void shift_register_set_state(shift_register_t *sr, uint64_t value)
{
	int i;

	for (i = 0; i < sr->count; i++) {
		en_gpio_write(sr->data, value & (1 << i));
		en_gpio_write(sr->clock, 1);
		en_gpio_write(sr->clock, 0);
	}

	/* Unleash the beast ! */
	en_gpio_write(sr->latch, 1);
	en_gpio_write(sr->latch, 0);
}

int
shift_register_set_output(shift_register_t *sr, int output, gpio_state_t state)
{
	if (state == 0)
		sr->current_value &= ~(1 << output);
	else
		sr->current_value |= (1 << output);

	shift_register_set_state(sr, sr->current_value);
	
	return 0;
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

void
shift_register_init()
{
	module_register(&shift_register_module);
}
