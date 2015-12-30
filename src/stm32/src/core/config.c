#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HAL.h"
#include "json.h"
#include "debug.h"
#include "config.h"
#include "module.h"

#define DEFAULT_BAUDRATE	115200

#define CONFIG_NAME		"config.txt"
#define FILENAME_MAX_LENGTH	32

extern uint8_t __config_start, __config_end;

void
config_init()
{
	json_value* value;
	FILE *config;
	json_char *buffer = NULL;
	int length = 0;
	char filename[FILENAME_MAX_LENGTH];
	debug_puts("Config init\r\n");

	snprintf(filename, FILENAME_MAX_LENGTH, "%s"CONFIG_NAME, hal_get_filesystem_prefix());

	config = fopen(filename, "r");
	if (config == NULL) {
		buffer = (json_char *) &__config_start;
		length = &__config_end - &__config_start;
		debug_puts("Using default configuration");
	}

	value = json_parse(buffer, length);

        if (value == NULL) {
                debug_puts("Unable to parse data\r\n");
        }

	module_json_parse(value);

        json_value_free(value);

	return;
}
