#include "HAL.h"
#include <stdlib.h>

hal_uart_t *
hal_uart_setup(const char *tx, const char *rx, unsigned int baudrate)
{
	return NULL;
}

int
hal_uart_write(hal_uart_t *uart, const uint8_t *data, unsigned int length)
{
	return 0;
}

int
hal_uart_read(hal_uart_t *uart, uint8_t *data, unsigned int length, unsigned int *ret_len)
{
	*ret_len = 0;
	return 0;
}
