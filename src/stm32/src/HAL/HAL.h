#ifndef _HAL_H
#define _HAL_H

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
hal_serial_puts(const char *str);

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
 * @return 0 on success, a positive value on error
 */
int
hal_debug_puts(const char *str);

#endif /* _HAL_H */
