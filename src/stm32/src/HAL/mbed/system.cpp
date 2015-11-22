#include "mbed.h"

extern "C" {
#include "config.h"
}

Serial pc_serial(USBTX, USBRX);

extern "C" void
hal_system_init()
{
	pc_serial.baud(115200);
}


extern "C" int
hal_serial_puts(const char *str)
{
	pc_serial.puts(str);

	return 0;
}


extern "C" int
hal_debug_puts(const char *str)
{
	pc_serial.puts(str);

	return 0;
}


extern "C" int
hal_serial_getc(char *c)
{
	*c = pc_serial.getc();

	return 0;
}
