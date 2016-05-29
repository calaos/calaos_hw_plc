#include "HAL.h"
#include "spi.h"
#include "i2c.h"
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

int
main()
{
	hal_system_init();

	/* TODO: need some initcall mecanism */
	spi_bus_init();
	i2c_bus_init();
	en_gpio_init();
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
