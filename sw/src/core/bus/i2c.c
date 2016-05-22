#define _GNU_SOURCE 1

#include "module.h"
#include "debug.h"
#include "utils.h"
#include "json.h"
#include "i2c.h"

#include <string.h>
#include <stdlib.h>

#define MAX_I2C_BUS	4	

static int g_max_i2c_bus_id = 0;
static struct i2c_bus *g_i2cs[MAX_I2C_BUS];

i2c_bus_t *
i2c_bus_get_by_name(const char *name) 
{
	int i;

	for (i = 0; i < g_max_i2c_bus_id; i++) {
		if (strncmp(name, g_i2cs[i]->name, strlen(name)) == 0)
			return g_i2cs[i];
	}

	return NULL;
}

static int
i2c_json_parse_one(json_value* json_i2c)
{
	int length, i;
	json_value *value;
	i2c_bus_t *i2cstruct;
	const char *name;
	char sda[10], scl[10];
	int freq = 1000000;

        i2cstruct = calloc(1, sizeof(struct i2c_bus));
        
        PANIC_ON(g_max_i2c_bus_id == MAX_I2C_BUS, "Too many i2c buses\r\n");

        length = json_i2c->u.object.length;
        for (i = 0; i < length; i++) {
		value = json_i2c->u.object.values[i].value;
		name = json_i2c->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			i2cstruct->name = strdup(value->u.string.ptr);
		} else if (strcmp(name, "sda") == 0) {
			strcpy(sda, value->u.string.ptr);
		} else if (strcmp(name, "scl") == 0) {
			strcpy(scl, value->u.string.ptr);
		} else if (strcmp(name, "freq") == 0) {
			freq = value->u.integer;
		}
        }

        i2cstruct->hal_i2c = hal_i2c_setup(sda, scl, freq);

	debug_puts("Adding i2c bus %s\r\n", i2cstruct->name);
	g_i2cs[g_max_i2c_bus_id++] = i2cstruct;

	return 0;
}


static int
i2c_json_parse(json_value* section)
{
        unsigned int i;

	for (i = 0; i < section->u.array.length; i++) {
		i2c_json_parse_one(section->u.array.values[i]);
	}
	return 0;
}




/**
 * Module
 */
static const module_t i2c_module = {
	.name = "i2c",
	.main_loop = NULL,
	.json_parse = i2c_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};


void
i2c_bus_init()
{
	module_register(&i2c_module);
}
