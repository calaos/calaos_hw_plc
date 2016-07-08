#include <string.h>

#include "HAL.h"
#include "spi.h"
#include "i2c.h"
#include "utils.h"
#include "debug.h"
#include "config.h"
#include "module.h"
#include "display.h"
#include "sensors.h"
#include "network.h"
#include "pcf8574.h"
#include "onewire.h"
#include "mysensors.h"
#include "shift_register.h"

unsigned int g_debug_enabled = 0;

static int
global_json_parse(json_value* section)
{
        unsigned int i, length;
	json_value *value;
	char *name;

	length = section->u.object.length;
	for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;

		if (strcmp(name, "debug") == 0) {
			g_debug_enabled = value->u.integer;
		}
	}

	serial_puts("Debug enabled: %d\r\n", g_debug_enabled);

	return 0;
}

/**
 * Module
 */
static const module_t global_module = {
	.name = "global",
	.main_loop = NULL,
	.json_parse = global_json_parse,
};

int
main()
{
	hal_system_init();

	/* TODO: need some initcall mecanism */
	/* Register global first */
	module_register(&global_module);

	gen_io_init();
	spi_bus_init();
	i2c_bus_init();
	en_gpio_init();
	/* Depends on gpio */
	onewire_bus_init();
	shift_register_init();
	pcf8574_init();
	mysensors_init();
	display_init();
	network_init();
	sensors_init();

	config_init();
	
	debug_puts("Entering main loop\r\n");
	while(1) {
		/* Main loop */
		module_main_loop();
	}
	
	return 0;
}
