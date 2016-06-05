#include "mbed.h"
#include "SDFileSystem.h"

#define SERIAL_RX_BUFFER_SIZE	128

SDFileSystem sd(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, "sd");

Serial pc_serial(USBTX, USBRX);
Serial debug_serial(PA_9, PA_10);
Timer t;

static char serial_rx_buffer[SERIAL_RX_BUFFER_SIZE];
static volatile uint8_t rx_head = 0, rx_tail = 0;

void serial_pc_rx_interrupt()
{
	uint8_t next_rx_tail = (rx_tail + 1) % SERIAL_RX_BUFFER_SIZE;

	while (pc_serial.readable() && next_rx_tail != rx_head) {
		serial_rx_buffer[rx_tail] = pc_serial.getc();
		rx_tail = next_rx_tail;
		next_rx_tail = (rx_tail + 1) % SERIAL_RX_BUFFER_SIZE;
	}
}

extern "C" void
hal_system_init()
{
	t.start();
	pc_serial.attach(&serial_pc_rx_interrupt, Serial::RxIrq);
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
	if (rx_head != rx_tail) {
		*c = serial_rx_buffer[rx_head];
		rx_head = (rx_head + 1) % SERIAL_RX_BUFFER_SIZE;
		return 1;
	}

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

