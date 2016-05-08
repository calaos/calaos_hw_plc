#define _GNU_SOURCE 1

#include "pcf8574.h"
#include "sensors.h"
#include "module.h"
#include "debug.h"
#include "generic_io.h"
#include "json.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>

#define MAX_PCF8574		8	

struct pcf8574 {
	gen_io_t *int_io;
	char *name;			/* Expander name */
	uint8_t output_value;		/* Count of output for this shift register */
	uint8_t input_value;		/* Cached input value */
	uint8_t addr;			/* I2C address of this expander */
	uint8_t need_update;
};

struct pcf8574_io {
	struct pcf8574 *exp;
	uint8_t index;
};

typedef struct pcf8574 pcf8574_t;
typedef struct pcf8574_io pcf8574_io_t;

static int g_max_pcf8574_id = 0;
static struct pcf8574 *g_pcf8574s[MAX_PCF8574];

pcf8574_t *
pcf8574_get_by_name(const char *name) 
{
	int i;

	for (i = 0; i < g_max_pcf8574_id; i++) {
		if (strncmp(name, g_pcf8574s[i]->name, strlen(name)) == 0)
			return g_pcf8574s[i];
	}

	return NULL;
}

static int
pcf8574_json_parse_one(json_value* sensor)
{
	int length, i;
	json_value *value;
	pcf8574_t *exp;
	const char *name;

        exp = calloc(1, sizeof(struct pcf8574));

        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			exp->name = strdup(value->u.string.ptr);
		} else if (strcmp(name, "addr") == 0) {
			exp->addr = value->u.integer;
		} else if (strcmp(name, "int") == 0) {
			exp->int_io = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		}
        }
        exp->output_value = 0;
        exp->need_update = 1;

	debug_puts("Adding pcf8574 %s with %d output\r\n", exp->name, exp->addr);
	g_pcf8574s[g_max_pcf8574_id++] = exp;

	return 0;
}


static int
pcf8574_json_parse(json_value* value)
{
        unsigned int i;
	json_value *section;

	section = config_get_section(value, "pcf8574s");
	if (!section)
		return -1;

	for (i = 0; i < section->u.array.length; i++) {
		pcf8574_json_parse_one(section->u.array.values[i]);
	}
	return 0;
}


static int
pcf8574_set_output(pcf8574_t *exp, uint8_t output, gpio_state_t state)
{

	if (state == 0)
		exp->output_value &= ~(1 << output);
	else
		exp->output_value |= (1 << output);

	exp->need_update = 1;
	hal_i2c_write(exp->addr, &exp->output_value, 1);

	return 0;
}

static void *
pcf8574_io_setup(const char *exp_io_name, __unused__ int reverse, 
	__unused__ gpio_dir_t direction, __unused__ gpio_debounce_t debounce)
{
	char name_cpy[GEN_IO_MAX_NAME_SIZE];
	char *sep;

	pcf8574_io_t *exp_io = calloc(1, sizeof(pcf8574_io_t));
	if (!exp_io)
		return NULL;
	strcpy(name_cpy, exp_io_name);

	/* FIXME: better error handling */
	sep = strchr(name_cpy, '@');
	PANIC_ON(sep == NULL, "Could not find @ separator in io name\n");

	sep[0] = '\0';
	exp_io->index = atoi(sep + 1);
	exp_io->exp = pcf8574_get_by_name(name_cpy);
	PANIC_ON(exp_io->exp == NULL, "Failed to get exp %s\n", name_cpy);

	return exp_io;
}
 
static void
pcf8574_io_write(void *io, gpio_state_t state)
{
	pcf8574_io_t *exp_io = io;
	
	pcf8574_set_output(exp_io->exp, exp_io->index, state);
}

static gpio_state_t
pcf8574_io_read(void *io)
{
	pcf8574_io_t *exp_io = io;

	/* if there was an interrupt, read the new value */
	if (gen_io_read(exp_io->exp->int_io) || exp_io->exp->need_update)
		hal_i2c_read(exp_io->exp->addr, &exp_io->exp->input_value, 1);

	return exp_io->exp->input_value & (1 << exp_io->index);
}

/**
 * Module
 */
static const module_t pcf8574_module = {
	.name = "pcf8574",
	.main_loop = NULL,
	.json_parse = pcf8574_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};

static const gen_io_ops_t pcf8574_io_ops = {
	.io_write = pcf8574_io_write,
	.io_read = pcf8574_io_read,
	.io_setup = pcf8574_io_setup,
	.prefix = "sr",
};

void
pcf8574_init()
{
	gen_io_ops_register(&pcf8574_io_ops);
	module_register(&pcf8574_module);
}
