#define _GNU_SOURCE 1

#include "generic_io.h"
#include "pcf8574.h"
#include "sensors.h"
#include "module.h"
#include "debug.h"
#include "queue.h"
#include "utils.h"
#include "json.h"
#include "i2c.h"

#include <string.h>
#include <stdlib.h>

struct pcf8574 {
	gen_io_t *int_io;
	i2c_bus_t *i2c;
	char *name;			/* Expander name */
	uint8_t output_value;		/* Count of output for this shift register */
	uint8_t input_value;		/* Cached input value */
	uint8_t addr;			/* I2C address of this expander */
	uint8_t need_update;
	uint8_t inputs;
	SLIST_ENTRY(pcf8574) link;
};

struct pcf8574_io {
	struct pcf8574 *exp;
	uint8_t index;
};

typedef struct pcf8574 pcf8574_t;
typedef struct pcf8574_io pcf8574_io_t;

static SLIST_HEAD(, pcf8574) g_pcf8574s = SLIST_HEAD_INITIALIZER();

pcf8574_t *
pcf8574_get_by_name(const char *name) 
{
	struct pcf8574 *pcf;

	SLIST_FOREACH(pcf, &g_pcf8574s, link) {
		if (strncmp(name, pcf->name, strlen(name)) == 0)
			return pcf;
	}

	return NULL;
}

static int
pcf8574_json_parse_one(json_value* sensor)
{
	int length, i;
	json_value *value;
	pcf8574_t *exp = NULL;
	const char *name;

        exp = calloc(1, sizeof(struct pcf8574));
        PANIC_ON(!exp, "Alloc failed");

        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			exp->name = strdup(value->u.string.ptr);
		} else if (strcmp(name, "addr") == 0) {
			exp->addr = strtol(value->u.string.ptr, NULL, 16);
		} else if (strcmp(name, "int") == 0) {
			exp->int_io = gen_io_setup(value->u.string.ptr, 1, GPIO_DIR_INPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_UP);
		} else if (strcmp(name, "i2c") == 0) {
			exp->i2c = i2c_bus_get_by_name(value->u.string.ptr);
		}
        }
        PANIC_ON(exp->i2c == NULL || exp->addr == 0 || exp->int_io == NULL,
			"Missing info for pcf8574\n");
        exp->output_value = 0;
        exp->need_update = 1;
	dbg_log("Adding pcf8574 %s with address 0x%x\n", exp->name, exp->addr);

	if (i2c_bus_read(exp->i2c, exp->addr, &exp->input_value, 1) != 0) {
		dbg_log("pcf8574 %s with address 0x%x did not answer, freeing\n", exp->name, exp->addr);
		free(exp);
		return 1;
	}

	SLIST_INSERT_HEAD(&g_pcf8574s, exp, link);
	return 0;
}


static int
pcf8574_json_parse(json_value* section)
{
        unsigned int i;
        int error = 0;

	for (i = 0; i < section->u.array.length; i++) {
		error |= pcf8574_json_parse_one(section->u.array.values[i]);
	}

	return error;
}


static int
pcf8574_set_output(pcf8574_t *exp, uint8_t output, int state)
{

	if (state == 0)
		exp->output_value &= ~(1 << output);
	else
		exp->output_value |= (1 << output);

	/* We must set input as high when writing output */
	exp->output_value |= exp->inputs;

	exp->need_update = 1;
	i2c_bus_write(exp->i2c, exp->addr, &exp->output_value, 1);

	return 0;
}

static void *
pcf8574_io_setup(const char *prefix, const char *exp_io_name, __unused__ int reverse, 
	__unused__ gpio_dir_t direction, __unused__ gpio_debounce_t debounce, __unused__ gpio_pin_mode_t mode)
{

	pcf8574_io_t *exp_io = calloc(1, sizeof(pcf8574_io_t));
	if (!exp_io)
		return NULL;

	exp_io->index = atoi(exp_io_name);
	exp_io->exp = pcf8574_get_by_name(prefix);
	PANIC_ON(exp_io->exp == NULL, "Failed to get exp %s\n", prefix);
	
	exp_io->exp->inputs |= (1 << exp_io->index);

	return exp_io;
}

static void
pcf8574_io_write(void *io, int state)
{
	pcf8574_io_t *exp_io = io;
	
	pcf8574_set_output(exp_io->exp, exp_io->index, state);
}

static int
pcf8574_io_read(void *io)
{
	pcf8574_io_t *exp_io = io;
	pcf8574_t *exp = exp_io->exp;
	int ret;

	/* if there was an interrupt, read the new value */
	if (gen_io_read(exp->int_io) || exp->need_update) {
		ret = i2c_bus_read(exp->i2c, exp->addr, &exp->input_value, 1);
		PANIC_ON(ret != 0, "Failed to read PCF");
		exp->need_update = 0;
	}

	return (exp->input_value >> exp_io->index) & 0x1;
}

/**
 * Module
 */
static const module_t pcf8574_module = {
	.name = "pcf8574",
	.main_loop = NULL,
	.json_parse = pcf8574_json_parse,
};

static gen_io_ops_t pcf8574_io_ops = {
	.io_write = pcf8574_io_write,
	.io_read = pcf8574_io_read,
	.io_setup = pcf8574_io_setup,
	.prefix = "pcf",
};

void
pcf8574_init()
{
	gen_io_ops_register(&pcf8574_io_ops);
	module_register(&pcf8574_module);
}
