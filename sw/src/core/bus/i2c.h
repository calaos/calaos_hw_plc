#ifndef _I2C_H
#define _I2C_H

#include "HAL.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prototype, public
 */

typedef struct i2c_bus i2c_bus_t;

i2c_bus_t *
i2c_bus_get_by_name(const char *name);

void
i2c_bus_init();

/**
 * Implementation, private
 */

struct i2c_bus {
	char *name;
	hal_i2c_t *hal_i2c;
};

static inline void
i2c_bus_write(i2c_bus_t *i2c, uint8_t addr, const uint8_t *data, unsigned int length)
{
	hal_i2c_write(i2c->hal_i2c, addr, data, length);
}

static inline void
i2c_bus_read(i2c_bus_t *i2c, uint8_t addr, uint8_t *data, unsigned int length)
{
	hal_i2c_read(i2c->hal_i2c, addr, data, length);
}

#ifdef __cplusplus
}
#endif

#endif
