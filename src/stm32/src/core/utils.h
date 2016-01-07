#ifndef _UTILS_H
#define _UTILS_H

#include "debug.h"
#include "HAL.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define __unused__ __attribute__ ((unused))

#define PANIC(format, ...) do { debug_puts("PANIC: " format, ##__VA_ARGS__); hal_panic(); } while(0);

#define PANIC_ON(test, format, ...) do { if (test) {PANIC(format, ##__VA_ARGS__);} } while(0);

void
serial_puts(const char *format, ...);

#endif
