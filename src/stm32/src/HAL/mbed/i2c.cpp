#include <mbed.h>
#include "mbed_util.h"

extern "C" {
#include "HAL.h"
}

/**
 * Initialize I2C bus from string
 */
extern "C" hal_i2c_bus_t *
hal_i2c_init(const char *scl, const char *sda, __attribute__((unused)) uint32_t frequency)
{
	I2C * i2c = new I2C(mbed_pinname_from_str(sda), mbed_pinname_from_str(scl));
	return (hal_i2c_bus_t *) i2c;
}

/**
 * Write data to I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data to send
 * @param length Length of data
 */
extern "C" void
hal_i2c_write(hal_i2c_bus_t *i2c_bus, uint8_t addr,
	const uint8_t *data, unsigned int length)
{
	I2C *i2c = (I2C *) i2c_bus;
	i2c->write(addr, (const char *) data, length);
}

/**
 * Read data from I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data read
 * @param length Length of data
 */
extern "C" void
hal_i2c_read(hal_i2c_bus_t *i2c_bus, uint8_t addr, 
	uint8_t *data, unsigned int length)
{
	I2C *i2c = (I2C *) i2c_bus;
	i2c->read(addr, (char *) data, length);
}

/**
 * Send a start condition on I2C bus
 * @param i2c_bus I2C bus to send data
 */
extern "C" void
hal_i2c_start(hal_i2c_bus_t *i2c_bus)
{
	I2C *i2c = (I2C *) i2c_bus;
	i2c->start();
}

/**
 * Send a stop condition on I2C bus
 * @param i2c_bus I2C bus to send data
 */
extern "C" void
hal_i2c_stop(hal_i2c_bus_t *i2c_bus)
{
	I2C *i2c = (I2C *) i2c_bus;
	i2c->stop();
}
