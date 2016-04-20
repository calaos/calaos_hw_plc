#ifndef _HAL_H
#define _HAL_H

#include <stdarg.h>
#include <inttypes.h>
#include "gpio.h"

/**
 * Initialize the system
 */
void
hal_system_init();

/**
 * Output a string on the serial port
 * @param str The string to output
 * @return 0 on success, a positive value on error
 */
int
hal_serial_puts(const char *format, ...);

/**
 * Get a char from the serial port
 * @param c Pointer to store the char
 * @return 0 if a char was received, a positive value if not.
 */
int
hal_serial_getc(char *c);

/**
 * Output a string on the serial port
 * @param str The string to output
 * @return 1 if there is a char, 0 if not
 */
int
hal_debug_puts(const char *str);

/**
 * Panic the system
 */
__attribute__((noreturn))
void
hal_panic(void);

/**
 * Get microseconds elapsed since start of program
 * @return Elapsed time in microseconds
 */
unsigned long long
hal_get_micro(void);

/**
 * Get milliseconds elapsed since start of program
 * @return Elapsed time in microseconds
 */
unsigned long long
hal_get_milli(void);

/**
 * GPIO
 */

typedef struct hal_gpio hal_gpio_t;

/**
 * Create a gpio object from parameters
 * @param gpio_name GPIO name
 * @param reverse Reverse the gpio direction
 * @param direction GPIO direction (input/output)
 */
hal_gpio_t *
hal_gpio_setup(const char *gpio_name, int reverse, gpio_dir_t direction);

/**
 * Set a gpio state
 * @param gpio The gpio to set value
 * @param state State to set
 * @return 0 on success, a positive value on error
 */
void
hal_gpio_write(hal_gpio_t *gpio, int state);

/**
 * Get a gpio state
 * @param gpio The gpio to get value from
 * @return gpio value
 */
int
hal_gpio_read(hal_gpio_t *gpio);

/**
 * Get filesystem prefix
 */
const char *
hal_get_filesystem_prefix();

/**
 * I2C
 */

/**
 * Initialize I2C bus 
 */
void
hal_i2c_init(uint32_t frequency);

/**
 * Write data to I2C bus
 * @param addr Address of device on i2c bus
 * @param data Data to send
 * @param length Length of data
 */
void
hal_i2c_write(uint8_t addr, const uint8_t *data, unsigned int length);

/**
 * Read data from I2C bus
 * @param addr Address of device on i2c bus
 * @param data Data read
 * @param length Length of data
 */
void
hal_i2c_read(uint8_t addr, uint8_t *data, unsigned int length);

/**
 * SPI
 */

/**
 * SPI init
 * @frequency Set the SPI to the desired frequency
 */
void
hal_spi_init(uint32_t frequency);

/**
 * Send a value through SPI
 * @value Value to send through SPI
 * @return Value read through SPI
 */
int
hal_spi_write(uint8_t value);


#endif /* _HAL_H */
