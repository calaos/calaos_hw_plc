#ifndef _SPI_H
#define _SPI_H

#include "HAL.h"
#include "queue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spi_bus spi_bus_t;

spi_bus_t *
spi_bus_get_by_name(const char *name);

void
spi_bus_init();

/**
 * Implementation, private
 */
struct spi_bus {
	char *name;
	hal_spi_t *hal_spi;
	SLIST_ENTRY(spi_bus) link;
};

static inline int
spi_bus_write(spi_bus_t *spi, uint8_t value)
{
	return hal_spi_write(spi->hal_spi, value);
}




#ifdef __cplusplus
}
#endif

#endif
