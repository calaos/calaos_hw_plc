#ifndef _HAL_H
#define _HAL_H

#include <stdarg.h>

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
void
hal_panic(void);

#endif /* _HAL_H */
