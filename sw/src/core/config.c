#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HAL.h"
#include "json.h"
#include "debug.h"
#include "config.h"
#include "module.h"
#include "utils.h"

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

	dbg_log("Config init\n");

	snprintf(filename, FILENAME_MAX_LENGTH, "%s"CONFIG_NAME, hal_get_filesystem_prefix());

	config = fopen(filename, "r");
	if (config == NULL) {
		dbg_log("Using default configuration\n");
		buffer = (json_char *) &__config_start;
		length = &__config_end - &__config_start;
	} else {
		dbg_log("Loading configuration from filesystem\n");
		fseek(config, 0, SEEK_END);

		length = ftell(config);
		rewind(config);
		buffer = malloc(length);
		PANIC_ON(!buffer, "Can not allocate enough memory");

		fread(buffer, 1, length, config);
	}

	value = json_parse(buffer, length);

	PANIC_ON(value == NULL, "Unable to parse data");

	if (config != NULL) {
		free(buffer);
		fclose(config);
	}

	module_json_parse(value);

        json_value_free(value);

	return;
}

json_value *
config_get_section(json_value *json, const char *section_name)
{
	int length, i;

        length = json->u.object.length;
        for (i = 0; i < length; i++) {
		if (strcmp(json->u.object.values[i].name, section_name) == 0) {
			dbg_log("Found section %s\n", section_name);
			return json->u.object.values[i].value;
		}
        }

        return NULL;
}
