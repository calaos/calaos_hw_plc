#include "HAL.h"
#include "utils.h"

/**
 * Initialize I2C bus from string
 */
hal_i2c_bus_t *
hal_i2c_init(const char *scl, const char *sda, uint32_t frequency)
{
	debug_puts("Opening I2C scl %s, sda %s, freq %d\n", scl, sda, frequency);
	return (void *) 1;
}

/**
 * Write data to I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data to send
 * @param length Length of data
 */
void
hal_i2c_write(__unused__ hal_i2c_bus_t *i2c_bus, uint8_t addr,
	__unused__ const uint8_t *data, __unused__ unsigned int length)
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
hal_i2c_read(__unused__ hal_i2c_bus_t *i2c_bus, uint8_t addr, 
	__unused__ uint8_t *data, __unused__ unsigned int length)
{	
	debug_puts("I2C read at addr %x\r\n", addr);
}

/**
 * Send a start condition on I2C bus
 * @param i2c_bus I2C bus to send data
 */
void
hal_i2c_start(__unused__ hal_i2c_bus_t *i2c_bus)
{
	debug_puts("I2C start condition\r\n");
}

/**
 * Send a stop condition on I2C bus
 * @param i2c_bus I2C bus to send data
 */
void
hal_i2c_stop(__unused__ hal_i2c_bus_t *i2c_bus)
{
	debug_puts("I2C stop condition\r\n");
}
