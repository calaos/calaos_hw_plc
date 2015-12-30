#include "HAL.h"
#include "utils.h"
#include "debug.h"
#include <stdarg.h>
#include <stdio.h>

#define MAX_BUF_SIZE	128

static char g_io_buffer[MAX_BUF_SIZE];

void
_debug_puts(const char *format, ...)
{
  va_list args;

  va_start(args, format);
  vsnprintf(g_io_buffer, sizeof(g_io_buffer), format, args);
  va_end(args);
  hal_debug_puts(g_io_buffer);
}

void
serial_puts(const char *format, ...)
{
  va_list args;

  va_start(args, format);
  vsnprintf(g_io_buffer, sizeof(g_io_buffer), format, args);
  va_end(args);
  hal_serial_puts(g_io_buffer);
}
