#include "display.h"
#include "ssd1306.h"
#include "module.h"
#include "utils.h"

#include <string.h>

static display_ops_t const *g_display_ops[] = {
	&ssd1306_display_ops,
};

typedef struct display {
	int width;
	int height;
} display_t;

static display_t g_display;

static display_ops_t const *g_current_display_ops;

static int
display_json_parse(json_value* value)
{
        unsigned int i, length;
	json_value *section;
	display_ops_t const *disp_ops;
	char *name;
	const char *type = NULL;

	section = config_get_section(value, "display");
	if (section) {
		length = section->u.object.length;
		for (i = 0; i < length; i++) {
			value = section->u.object.values[i].value;
			name = section->u.object.values[i].name;

			if (strcmp(name, "type") == 0) {
				type = value->u.string.ptr;
			} else if (strcmp(name, "width") == 0) {
				g_display.width = value->u.integer;
			} else if (strcmp(name, "height") == 0) {
				g_display.height = value->u.integer;
			}
		}
		debug_puts("Setup display w %d, h %d\r\n", g_display.width, g_display.height);

		for (i = 0; i < ARRAY_SIZE(g_display_ops); i++) {
			disp_ops = g_display_ops[i];
			if (strncmp(disp_ops->name, type, strlen(disp_ops->name)) == 0) {
				g_current_display_ops = disp_ops;
				disp_ops->init(type, g_display.width, g_display.height);
				return 0;
			}
				
		}
		PANIC("Failed to find display matching configuration\r\n");
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
