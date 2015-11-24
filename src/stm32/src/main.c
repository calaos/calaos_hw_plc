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
	
	debug_puts("Entering main loop\r\n");
	while(1) {
		/* Main loop */
	}
	
	return 0;
}
