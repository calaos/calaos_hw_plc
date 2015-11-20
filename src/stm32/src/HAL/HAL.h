#ifndef _HAL_H
#define _HAL_H

/**
 * Initialize the system
 */
void hal_system_init();

/**
 * Output a string on the serial port
 * @param str The string to output
 * @return 0 on success, a positive value on error
 */
int hal_serial_puts(const char *str);

/**
 * Get a string on the serial port
 * @param str The string to output
 * @return 0 on success, a positive value on error
 */
int hal_serial_gets(char *str, int strlen);

#endif /* _HAL_H */
