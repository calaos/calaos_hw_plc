#include "HAL.h"
#include "debug.h"
#include "config.h"
#include "module.h"
#include "mysensors.h"
#include "sensors.h"

int
main()
{
	hal_system_init();

	mysensors_init();
	sensors_init();
	en_gpio_init();

	config_init();
	
	debug_puts("Entering main loop\r\n");
	while(1) {
		/* Main loop */
		module_main_loop();
	}
	
	return 0;
}
