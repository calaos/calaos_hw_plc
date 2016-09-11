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
#include "communication.h"
#include "shift_register.h"

int
main()
{
	hal_system_init();

	/* TODO: need some initcall mecanism */
	communication_init();

	gen_io_init();
	spi_bus_init();
	i2c_bus_init();
	en_gpio_init();

	network_init();
	/* Depends on gpio */
	onewire_bus_init();
	shift_register_init();
	pcf8574_init();
	mysensors_init();
	display_init();
	sensors_init();

	config_init();
	
	dbg_log("Entering main loop\n");
	while(1) {
		/* Main loop */
		module_main_loop();
	}
	
	return 0;
}
