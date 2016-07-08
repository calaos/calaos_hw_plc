#ifndef _DEBUG_H
#define _DEBUG_H


#ifdef __cplusplus
extern "C" {
#endif

void
_debug_puts(const char *format, ...);

extern unsigned int g_debug_enabled;
#ifdef __cplusplus
}
#endif

#ifndef DEBUG_DISABLE
#define debug_puts(format, ...) if (g_debug_enabled) {_debug_puts ("[DBG] " format, ##__VA_ARGS__);}
#else
#define debug_puts(format, ...)	do { if (0) _debug_puts (format, ##__VA_ARGS__); } while(0)
#endif

#endif
