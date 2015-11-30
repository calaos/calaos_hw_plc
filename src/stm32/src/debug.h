#ifndef _DEBUG_H
#define _DEBUG_H

void
_debug_puts(const char *format, ...);

#ifndef NDEBUG
#define debug_puts(format, ...) _debug_puts (format, ##__VA_ARGS__)
#else
#define debug_puts(format, ...)	do { if (0) _debug_puts (format, ##__VA_ARGS__); } while(0)
#endif

#endif
