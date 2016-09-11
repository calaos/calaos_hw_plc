#define _GNU_SOURCE 1

#include "module.h"
#include "debug.h"
#include "queue.h"
#include "utils.h"
#include "json.h"
#include "i2c.h"

#include <string.h>
#include <stdlib.h>

static SLIST_HEAD(, i2c_bus) g_i2cs = SLIST_HEAD_INITIALIZER();

i2c_bus_t *
i2c_bus_get_by_name(const char *name) 
{
	struct i2c_bus *bus;
	
	SLIST_FOREACH(bus, &g_i2cs, link) {
		if (strncmp(name, bus->name, strlen(name)) == 0)
			return bus;
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
	int freq = 100000;

	i2cstruct = calloc(1, sizeof(struct i2c_bus));

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
	PANIC_ON(!i2cstruct->hal_i2c, "Failed to setup I2C bus");

	dbg_log("Adding i2c bus %s, speed %d, sda %s, scl %s\n", i2cstruct->name, freq, sda, scl);
	SLIST_INSERT_HEAD(&g_i2cs, i2cstruct, link);

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
};


void
i2c_bus_init()
{
	module_register(&i2c_module);
}
