#ifndef _UTILS_H
#define _UTILS_H

#include "debug.h"
#include "HAL.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define __unused__ __attribute__ ((unused))
 
#define PANIC(format, ...) do { dbg_log("PANIC: " format "\n", ##__VA_ARGS__); hal_panic(); } while(0);

#define PANIC_ON(test, format, ...) do { if (test) {PANIC(format, ##__VA_ARGS__);} } while(0);

static inline void ms_delay(unsigned long long ms)
{
	ms *= 1000;
	volatile unsigned long long now, present = hal_get_micro();

	do {
		now = hal_get_micro();
	} while ((now - present) < ms);
}

static inline void us_delay(unsigned long long us)
{
	volatile unsigned long long now, present = hal_get_micro();

	do {
		now = hal_get_micro();
	} while ((now - present) < us);
}

#endif
