#include "mbed.h"

extern "C" {
#include "config.h"
}

Serial pc_serial(USBTX, USBRX);

extern "C" void hal_system_init()
{
	int baudrate;
	config_get_int("baudrate", &baudrate);
	
	pc_serial.baud(baudrate);
}


int hal_serial_puts(const char *str)
{
	pc_serial.printf("%s\n", str);
	return 0;
}
