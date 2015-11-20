#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ini.h"
#include "config.h"

#define DEFAULT_BAUDRATE	115200

extern uint8_t __config_start, __config_end;

/* FIXME: crap, need a hash system */
static int baudrate;

static char *config_ini_reader(char* str, int num, void* stream)
{
	static unsigned int cur_stream_pos = 0;
	char *bin_stream = stream;
	unsigned int i = 0;

	while (1) {
		/* We hit the end of config section */
		if ( (&__config_start + cur_stream_pos) == &__config_end)
			return NULL;

		if (bin_stream[cur_stream_pos] == '\n')
			return str;


		str[i++] = bin_stream[cur_stream_pos++];
	}
}

static int config_ini_handler(void* user, const char* section, const char* name, const char* value)
{
	if (strcmp(name, "baudrate") == 0)
		baudrate = atoi(value);

	return 0;
}

void config_init()
{
	/* TODO read from a sd card or something like that */
	ini_parse_stream(config_ini_reader, &__config_start, config_ini_handler, NULL);

	return;
}

int config_get_str(const char *str, char *value, unsigned int len)
{
	return 1;
}

int config_get_int(const char *str, int *value)
{
	if (strcmp(str, "baudrate") == 0) {
		*value = baudrate;
	} else {
		return 1;
	}

	return 0;
}
