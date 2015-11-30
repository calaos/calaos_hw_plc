#include "HAL.h"
#include "debug.h"
#include <stdarg.h>
#include <stdio.h>

#define MAX_BUF_SIZE	2048

void
_debug_puts(const char *format, ...)
{
  va_list args;
  char buffer[MAX_BUF_SIZE] = "[DBG] ";

  va_start(args, format);
  vsnprintf(buffer + 6, sizeof buffer, format, args);
  va_end(args);
  hal_debug_puts(buffer);
}
