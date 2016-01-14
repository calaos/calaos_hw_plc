#include <mbed.h>
#include "mbed_util.h"

extern "C" {
#include "HAL.h"
}

I2C i2c(I2C_SDA, I2C_SCL);

/**
 * Initialize I2C bus from string
 */
extern "C" void
hal_i2c_init(__attribute__((unused)) uint32_t frequency)
{
}

/**
 * Write data to I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data to send
 * @param length Length of data
 */
extern "C" void
hal_i2c_write(uint8_t addr,
	const uint8_t *data, unsigned int length)
{
	i2c.write(addr, (const char *) data, length);
}

/**
 * Read data from I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data read
 * @param length Length of data
 */
extern "C" void
hal_i2c_read(uint8_t addr, 
	uint8_t *data, unsigned int length)
{
	i2c.read(addr, (char *) data, length);
}

