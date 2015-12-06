#ifndef _UTILS_H
#define _UTILS_H

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define __unused__ __attribute__ ((unused))

#define PANIC() do { debug_puts("PANIC: %s : %d\r\n"); hal_panic(); } while(0);

#endif
