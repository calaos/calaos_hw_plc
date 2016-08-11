#include "HAL.h"
#include "utils.h"

#include <stdlib.h>

hal_spi_t *
hal_spi_setup(const char *mosi, const char *miso, const char *sck, uint32_t frequency)
{
	dbg_log("SPI: init freq %d\n", frequency);

	return NULL;
}

/**
 * Send a value through SPI
 * @value Value to send through SPI
 */
int
hal_spi_write(hal_spi_t *spi, uint8_t value)
{
	return 0;
}
