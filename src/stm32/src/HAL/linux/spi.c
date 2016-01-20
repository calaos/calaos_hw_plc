#include "HAL.h"
#include "utils.h"


void
hal_spi_init(uint32_t frequency)
{
	debug_puts("SPI: init freq %d\n", frequency);
}

/**
 * Send a value through SPI
 * @value Value to send through SPI
 */
int
hal_spi_write(uint8_t value)
{
	debug_puts("SPI: writing value %x\n", value);
	return 0;
}
