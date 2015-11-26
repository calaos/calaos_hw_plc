#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HAL.h"
#include "json.h"
#include "debug.h"
#include "config.h"
#include "module.h"

#define DEFAULT_BAUDRATE	115200

extern uint8_t __config_start, __config_end;

void
config_init()
{
	json_value* value;
	debug_puts("Config init\r\n");

	value = json_parse((json_char*) &__config_start, &__config_end - &__config_start);

        if (value == NULL) {
                debug_puts("Unable to parse data\r\n");
        }

	module_json_parse(value);

        json_value_free(value);
        

	return;
}

int
config_get_int(const char *str, int *value)
{
	return 0;
}
