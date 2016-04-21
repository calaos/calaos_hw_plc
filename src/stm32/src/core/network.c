#include "wiznet_iface.h"
#include "network.h"
#include "module.h"
#include "utils.h"

#include <string.h>

static int
network_init_interface()
{
	return 0;
}

static int
network_json_parse(json_value* value)
{
        unsigned int i, length;
	json_value *section, __unused__ *data = NULL;
	char *name;
	__unused__ const char *type = NULL;

	section = config_get_section(value, "net");
	if (!section)
		return -1;

	length = section->u.object.length;
	for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;

		if (strcmp(name, "type") == 0) {
			type = value->u.string.ptr;
		} else if (strcmp(name, "data") == 0) {
			data = value;
		}
	}

	return network_init_interface();
}

/**
 * Module
 */
static const module_t network_module = {
	.name = "network",
	.main_loop = NULL,
	.json_parse = network_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};

void
network_init()
{
	module_register(&network_module);
}
