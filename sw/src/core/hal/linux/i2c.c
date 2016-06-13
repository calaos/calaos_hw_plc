#include "HAL.h"
#include "utils.h"

#include <stdlib.h>

/**
 * Initialize I2C bus from string
 */
hal_i2c_t *
hal_i2c_setup(const char *sda, const char *scl, uint32_t frequency)
{
	debug_puts("Init i2c freq %d\n", frequency);
	return NULL;
}

/**
 * Write data to I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data to send
 * @param length Length of data
 */
int
hal_i2c_write(hal_i2c_t *i2c, uint8_t addr, const uint8_t *data, unsigned int length)
{
	debug_puts("I2C write at addr %x\r\n", addr);
}

/**
 * Read data from I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data read
 * @param length Length of data
 */
int
hal_i2c_read(hal_i2c_t *i2c, uint8_t addr, uint8_t *data, unsigned int length)
{	
	debug_puts("I2C read at addr %x\r\n", addr);
}
