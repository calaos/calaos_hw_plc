#ifndef _SPI_H
#define _SPI_H

#include "HAL.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spi_bus spi_bus_t;

/**
 * Spi bus struct
 */
struct spi_bus {
	char *name;
	hal_spi_t *hal_spi;
};


spi_bus_t *
spi_bus_get_by_name(const char *name);

static inline int
spi_bus_write(spi_bus_t *spi, uint8_t value)
{
	return hal_spi_write(spi->hal_spi, value);
}

void
spi_bus_init();

#ifdef __cplusplus
}
#endif

#endif
