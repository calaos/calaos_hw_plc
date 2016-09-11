#define _GNU_SOURCE 1

#include "module.h"
#include "utils.h"
#include "queue.h"
#include "debug.h"
#include "json.h"
#include "spi.h"

#include <string.h>
#include <stdlib.h>

static SLIST_HEAD(, spi_bus) g_spis = SLIST_HEAD_INITIALIZER();

spi_bus_t *
spi_bus_get_by_name(const char *name) 
{
	struct spi_bus *bus;

	SLIST_FOREACH(bus, &g_spis, link) {
		if (strncmp(name, bus->name, strlen(name)) == 0)
			return bus;
	}

	return NULL;
}

static int
spi_json_parse_one(json_value* json_spi)
{
	int length, i;
	json_value *value;
	spi_bus_t *spibus;
	const char *name;
	char mosi[10], miso[10], sck[10];
	int freq = 1000000;

        spibus = calloc(1, sizeof(struct spi_bus));

        length = json_spi->u.object.length;
        for (i = 0; i < length; i++) {
		value = json_spi->u.object.values[i].value;
		name = json_spi->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			spibus->name = strdup(value->u.string.ptr);
		} else if (strcmp(name, "mosi") == 0) {
			strcpy(mosi, value->u.string.ptr);
		} else if (strcmp(name, "miso") == 0) {
			strcpy(miso, value->u.string.ptr);
		} else if (strcmp(name, "sck") == 0) {
			strcpy(sck, value->u.string.ptr);
		} else if (strcmp(name, "freq") == 0) {
			freq = value->u.integer;
		}
        }

        spibus->hal_spi = hal_spi_setup(mosi, miso, sck, freq);

	dbg_log("Adding spi bus %s\n", spibus->name);
	SLIST_INSERT_HEAD(&g_spis, spibus, link);
	return 0;
}


static int
spi_json_parse(json_value* section)
{
        unsigned int i;

	for (i = 0; i < section->u.array.length; i++) {
		spi_json_parse_one(section->u.array.values[i]);
	}
	return 0;
}




/**
 * Module
 */
static const module_t spi_module = {
	.name = "spi",
	.main_loop = NULL,
	.json_parse = spi_json_parse,
};


void
spi_bus_init()
{
	module_register(&spi_module);
}
