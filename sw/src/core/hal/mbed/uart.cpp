extern "C" {
#include "HAL.h"
}
#include <mbed.h>

#include "mbed_util.h"

#define SERIAL_RX_BUFFER_SIZE	128

struct hal_uart;

class uart_cb
{
public:
    void callback();

    struct hal_uart *uart;
};

struct hal_uart {
	char rx_buffer[SERIAL_RX_BUFFER_SIZE];
	volatile uint8_t rx_head = 0, rx_tail = 0;
	Serial *serial;
	uart_cb *cb;
};

void uart_cb::callback() 
{
	struct hal_uart  *uart = this->uart;

	uint8_t next_rx_tail = (uart->rx_tail + 1) % SERIAL_RX_BUFFER_SIZE;

	while (uart->serial->readable() && next_rx_tail != uart->rx_head) {
		uart->rx_buffer[uart->rx_tail] = uart->serial->getc();
		uart->rx_tail = next_rx_tail;
		next_rx_tail = (uart->rx_tail + 1) % SERIAL_RX_BUFFER_SIZE;
	}
}

int
hal_uart_write(hal_uart_t *uart, const uint8_t *data, unsigned int length)
{
	struct hal_uart  *uartp = uart;
	unsigned int i;

	for (i = 0; i < length; i++)
		uartp->serial->putc(data[i]);
	
	return 0;
}

extern "C" int
hal_uart_read(hal_uart_t *uart, uint8_t *data, unsigned int length, unsigned int *ret_len)
{
	struct hal_uart  *uartp = uart;
	unsigned int i = 0;

	while (uartp->rx_head != uartp->rx_tail) {
		data[i++] = uartp->rx_buffer[uartp->rx_head];
		uartp->rx_head = (uartp->rx_head + 1) % SERIAL_RX_BUFFER_SIZE;
		return 1;
	}
	
	*ret_len = i;

	return 0;
}


extern "C" hal_uart_t *
hal_uart_setup(const char *tx, const char *rx, unsigned int baudrate)
{
	PinName tx_pin, rx_pin;
	struct hal_uart *uart = (struct hal_uart *) calloc(1, sizeof(struct hal_uart));
	if (!uart)
		return NULL;

	tx_pin = mbed_pinname_from_str(tx);
	rx_pin = mbed_pinname_from_str(rx);

	uart->serial = new Serial(tx_pin, rx_pin);
	if (!uart->serial)
		return NULL;

	uart->cb = new uart_cb();
	if (!uart->cb)
		return NULL;

	uart->cb->uart = uart;

	uart->serial->attach(uart->cb, &uart_cb::callback, Serial::RxIrq);
	uart->serial->baud(115200);

	return (hal_uart_t *) uart;
}
