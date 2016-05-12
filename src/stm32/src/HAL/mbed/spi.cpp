extern "C" {
#include "HAL.h"
}
#include <mbed.h>

#include "mbed_util.h"

SPI spi(SPI_MOSI, SPI_MISO, SPI_SCK);

extern "C" void
hal_spi_init(uint32_t frequency)
{
	spi.format(8,0);
	spi.frequency(frequency);
}

/**
 * Send a value through SPI
 * @value Value to send through SPI
 */
extern "C" int
hal_spi_write(hal_spi_t *spi, uint8_t value);
{
	
	return spi.write(value);
}
