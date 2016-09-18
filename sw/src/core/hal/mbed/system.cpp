#include "mbed.h"
#include "SDFileSystem.h"

SDFileSystem sd(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, "sd");

Serial pc_serial(USBTX, USBRX);
Timer t;


extern "C" void
hal_system_init()
{
	t.start();
	pc_serial.baud(115200);
}

extern "C" void
hal_serial_set_baudrate(int baudrate)
{
	pc_serial.baud(baudrate);
}


extern "C" int
hal_serial_puts(const char *str)
{
	pc_serial.puts(str);

	return 0;
}


extern "C" int
hal_dbg_log(const char *str)
{
	pc_serial.puts(str);

	return 0;
}

extern "C" void
hal_panic(void)
{
	DigitalOut led(LED1);
	while(1) {
		led = 1;
		wait(0.2);
		led = 0;
		wait(0.2);
	}
}

extern "C" unsigned long long
hal_get_micro(void)
{
	return t.read_us();
}


extern "C" unsigned long long
hal_get_milli(void)
{
	return t.read_ms();
}

extern "C" const char *
hal_get_filesystem_prefix()
{
	return "/sd/";
}

extern "C" void
hal_critical_enter()
{
	__disable_irq();
}

extern "C" void
hal_critical_exit() {
	__enable_irq();
}

