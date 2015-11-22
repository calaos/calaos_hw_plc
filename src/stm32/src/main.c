#include "HAL.h"
#include "config.h"
#include "mysensor.h"
#include "debug.h"

int
main()
{
	hal_system_init();
	config_init();
	
	mysensor_init();

	mysensor_create_sensor(S_LIGHT, "SW1");
	
	debug_puts("Entering main loop\r\n");
	while(1) {
		/* Main loop */
	}
	
	return 0;
}
