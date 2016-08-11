#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

void
dbg_puts(const char *format, ...);

extern unsigned int g_debug_enabled;

#ifdef __cplusplus
}
#endif

#ifndef DEBUG_DISABLE
#define dbg_log(format, ...) if (g_debug_enabled) {dbg_puts ("[DBG] " format, ##__VA_ARGS__);}
#else
#define dbg_log(format, ...)	do { if (0) dbg_puts (format, ##__VA_ARGS__); } while(0)
#endif

#endif
