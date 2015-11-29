#include <stdio.h>

void
hal_system_init()
{
	
}

int
hal_serial_puts(const char *str)
{
	puts(str);

	return 0;
}


int
hal_debug_puts(const char *str)
{
	puts(str);

	return 0;
}

int
hal_serial_getc(char *c)
{
	*c = getchar();

	return 0;
}
