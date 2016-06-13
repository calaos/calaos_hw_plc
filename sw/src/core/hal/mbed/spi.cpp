extern "C" {
#include "HAL.h"
}
#include <mbed.h>

#include "mbed_util.h"

extern "C" hal_spi_t *
hal_spi_setup(const char *mosi, const char *miso, const char *sck, uint32_t frequency)
{
	PinName pmosi, pmiso, psck;
	SPI *spi;
	
	pmosi = mbed_pinname_from_str(mosi);
	pmiso = mbed_pinname_from_str(miso);
	psck = mbed_pinname_from_str(sck);
	if (pmosi == NC || pmiso == NC || psck == NC)
		return NULL;

	spi = new SPI(pmosi, pmiso, psck);
	if (!spi)
		return NULL;

	spi->format(8, 0);
	spi->frequency(frequency);

	return (hal_spi_t *) spi;
}

/**
 * Send a value through SPI
 * @value Value to send through SPI
 */
extern "C" int
hal_spi_write(hal_spi_t *spi, uint8_t value)
{
	
	SPI *pspi = (SPI *) spi;
	return pspi->write(value);
}
