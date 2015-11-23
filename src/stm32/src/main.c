#include "HAL.h"
#include "debug.h"
#include "config.h"
#include "module.h"
#include "mysensor.h"

int
main()
{
	hal_system_init();
	
	mysensor_init();
	config_init();

	mysensor_create_sensor(S_LIGHT, "SW1");
	
	debug_puts("Entering main loop\r\n");
	while(1) {
		/* Main loop */
	}
	
	return 0;
}
