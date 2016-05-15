#include <mbed.h>
#include "mbed_util.h"

extern "C" {
#include "HAL.h"
}

/**
 * Initialize I2C bus from string
 */
extern "C" hal_i2c_t *
hal_i2c_setup(const char *sda, const char *scl, uint32_t frequency)
{
	PinName psda, pscl;
	psda = mbed_pinname_from_str(sda);
	pscl = mbed_pinname_from_str(scl);
	if (psda == NC || pscl == NC)
		return NULL;

	return (hal_i2c_t *) new I2C(psda, pscl);
}

/**
 * Write data to I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data to send
 * @param length Length of data
 */
extern "C" void
hal_i2c_write(hal_i2c_t *i2c, uint8_t addr,
		const uint8_t *data, unsigned int length)
{
	I2C *pi2c = (I2C *) i2c;
	pi2c->write(addr << 1, (const char *) data, length);
}

/**
 * Read data from I2C bus
 * @param i2c_bus I2C bus to send data
 * @param addr Address of device on i2c bus
 * @param data Data read
 * @param length Length of data
 */
extern "C" void
hal_i2c_read(hal_i2c_t *i2c, uint8_t addr,
		uint8_t *data, unsigned int length)
{
	I2C *pi2c = (I2C *) i2c;
	pi2c->read(addr << 1, (char *) data, length);
}

