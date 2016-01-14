#include "HAL.h"
#include "utils.h"

/**
 * Initialize I2C bus from string
 */
void
hal_i2c_init(uint32_t frequency)
{
	debug_puts("Init i2c freq %d\n", frequency);
}

/**
 * Write data to I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data to send
 * @param length Length of data
 */
void
hal_i2c_write(uint8_t addr, __unused__ const uint8_t *data, __unused__ unsigned int length)
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
void
hal_i2c_read(uint8_t addr, __unused__ uint8_t *data, __unused__ unsigned int length)
{	
	debug_puts("I2C read at addr %x\r\n", addr);
}
