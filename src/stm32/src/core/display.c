#include "module.h"
#include "utils.h"

#include <string.h>


typedef struct display {
	int width, height;
	int color;
	uint8_t *framebuffer;
} display_t;

static display_t g_display;

static int
display_json_parse(json_value* value)
{
        unsigned int i, length;
	json_value *section;
	char *name;

	section = config_get_section(value, "display");
	if (section) {
		length = section->u.object.length;
		for (i = 0; i < length; i++) {
			value = section->u.object.values[i].value;
			name = section->u.object.values[i].name;

			if (strcmp(name, "type") == 0) {
				/* FIXME */
			} else if (strcmp(name, "width") == 0) {
				g_display.width = value->u.integer;
			} else if (strcmp(name, "height") == 0) {
				g_display.height = value->u.integer;
			}
		}

		/* Framebuffer as a bitfield*/
		g_display.framebuffer = malloc(g_display.width * g_display.height / 8);
		PANIC_ON(!g_display.framebuffer, "Failed to allocate framebuffer");

		debug_puts("Setup display w %d, h %d\r\n", g_display.width, g_display.height);
		return 0;
	}

	return -1;
}

/**
 * Module
 */
const module_t display_module = {
	.name = "display",
	.main_loop = NULL,
	.json_parse = display_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};

void
display_init()
{
	module_register(&display_module);
}
