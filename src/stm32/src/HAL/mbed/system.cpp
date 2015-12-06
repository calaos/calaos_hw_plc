#include "mbed.h"

extern "C" {
#include "config.h"
}


Serial pc_serial(USBTX, USBRX);
Serial debug_serial(PA_9, PA_10);


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
	debug_serial.puts(str);

	return 0;
}


extern "C" int
hal_serial_getc(char *c)
{
	if (pc_serial.readable()) {
		*c = pc_serial.getc();
		return 1;
	}

	return 0;
}

DigitalOut led(LED1);

extern "C" void
hal_panic(void)
{
	while(1) {
		led = 1;
		wait(0.2);
		led = 0;
		wait(0.2);
	}
}
