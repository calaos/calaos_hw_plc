#include "display.h"
#include "ssd1306.h"
#include "ili9341.h"
#include "module.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>

/* Refresh every minute */
#define DISPLAY_REFRESH_TIME	(1000)

static display_ops_t const *g_display_ops[] = {
	&ssd1306_display_ops,
	&ili9341_display_ops,
};

typedef struct display {
	int width;
	int height;
	uint32_t colors[COLOR_COUNT];
	unsigned long long last_refresh;
	display_ops_t const *ops;
} display_t;

static display_t g_display = {0, 0, {0}, 0, NULL};

static void
display_print_char(int x, int y, char c, uint32_t color, uint32_t bg_color)
{
	uint8_t i, j, col;

	for(i = 0; i <= DISP_FONT_WIDTH; i++ ) {
		if (i >= g_display.width)
			return;

		if(i < DISP_FONT_WIDTH)
			col = g_display_font[(c * DISP_FONT_WIDTH) + i];
		else
			col = 0x0;

		for(j = 0; j < DISP_FONT_HEIGHT; j++, col >>= 1) {
			if (i >= g_display.height)
				return;

			if(col & 0x1) {
				g_display.ops->draw_pixel(x + i, y + j, color);
			} else {
				g_display.ops->draw_pixel(x + i, y + j, bg_color);
			}
		}
	}
}

static void
display_print(int x, int y, const char *str, uint32_t color, uint32_t bg_color)
{
	while (*str) {
		x += DISP_FONT_WIDTH +1;
		if (x > g_display.width)
			return;

		display_print_char(x, y, *str, color, bg_color);
		str++;
	}
}


static int
display_init_screen()
{
	int i;

	/* Initialize colors */
	for(i = 0; i < COLOR_COUNT; i++)
		g_display.colors[i] = g_display.ops->color_from_rgb(rgb_colors[i][0], rgb_colors[i][1], rgb_colors[i][2]);

	g_display.ops->init(g_display.width, g_display.height);
	display_print(0, 0, "Calaos PLC", g_display.colors[COLOR_NAVY], g_display.colors[COLOR_BLACK]);
	g_display.ops->disp();

	return 0;
}

static int
display_json_parse(json_value* section)
{
        unsigned int i, length;
	json_value *value, *disp_data = NULL;
	display_ops_t const *disp_ops;
	char *name;
	const char *type = NULL;

	length = section->u.object.length;
	for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;

		if (strcmp(name, "type") == 0) {
			type = value->u.string.ptr;
		} else if (strcmp(name, "data") == 0) {
			disp_data = value;
		} else if (strcmp(name, "width") == 0) {
			g_display.width = value->u.integer;
		} else if (strcmp(name, "height") == 0) {
			g_display.height = value->u.integer;
		}
	}
	PANIC_ON(!disp_data, "Failed to find display data section");
	dbg_log("Setup display w %d, h %d\n", g_display.width, g_display.height);

	for (i = 0; i < ARRAY_SIZE(g_display_ops); i++) {
		disp_ops = g_display_ops[i];
		if (strncmp(disp_ops->name, type, strlen(disp_ops->name)) == 0) {
			g_display.ops = disp_ops;
			break;
		}
	}
	PANIC_ON(!g_display.ops, "Failed to find display matching configuration");

	g_display.ops->parse_json(disp_data);
	display_init_screen();
	return 0;
}

static void
display_main_loop()
{
	unsigned long long time = hal_get_milli();
	unsigned int h, s, m;
	char buffer[10];
	div_t qr;

	if ((time - g_display.last_refresh) < DISPLAY_REFRESH_TIME)
		return;

	g_display.last_refresh = time;

	qr = div(time, 1000 * 60 * 60);
	h = qr.quot;

	qr = div(qr.rem, 1000 * 60);
	m = qr.quot;

	qr = div(qr.rem, 1000);
	s = qr.quot;

	snprintf(buffer, 10, "%02d:%02d:%02d\n", h, m, s);
	dbg_log("Uptime: %s\n", buffer);

	display_print(0, 0, "Uptime:   ", g_display.colors[COLOR_NAVY], g_display.colors[COLOR_BLACK]);
	display_print(0, 10, buffer, g_display.colors[COLOR_RED], g_display.colors[COLOR_BLACK]);

	g_display.ops->disp();
}

/**
 * Module
 */
static const module_t display_module = {
	.name = "display",
	.main_loop = display_main_loop,
	.json_parse = display_json_parse,
};

void
display_init()
{
	module_register(&display_module);
}
