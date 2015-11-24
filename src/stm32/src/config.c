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

static void process_value(json_value* value);

static void process_object(json_value* value)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.object.length;
        for (x = 0; x < length; x++) {
                debug_puts("object[%d].name = %s\r\n", x, value->u.object.values[x].name);
                process_value(value->u.object.values[x].value);
        }
}

static void process_value(json_value* value)
{
        if (value == NULL) {
                return;
        }

        switch (value->type) {
                case json_object:
                        process_object(value);
                        break;
                default:
                        break;
        }
}

void
config_init()
{
	json_value* value;
	debug_puts("Config init\r\n");

	value = json_parse((json_char*) &__config_start, &__config_end - &__config_start);

        if (value == NULL) {
                debug_puts("Unable to parse data\r\n");
        }
	process_value(value);

        json_value_free(value);

	return;
}

int
config_get_int(const char *str, int *value)
{
	return 0;
}
