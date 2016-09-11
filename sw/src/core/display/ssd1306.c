#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ssd1306.h"
#include "utils.h"
#include "i2c.h"
#include "HAL.h"

static uint8_t g_ssd1306_address = 0;
static uint8_t *g_ssd1306_buffer;
static uint32_t g_ssd1306_width, g_ssd1306_height;
static i2c_bus_t *g_ssd1306_i2c = NULL;

void
ssd1306_send_command(uint8_t command)
{
	uint8_t cmd[2] = {0x00, command};

	i2c_bus_write(g_ssd1306_i2c, g_ssd1306_address, cmd, 2);
}

static const uint8_t ssd1306_init_data[] = {
	SSD1306_DISPLAYOFF,
	SSD1306_SETDISPLAYCLOCKDIV,
	0x80,
	SSD1306_SETMULTIPLEX,
	0x3F,
	SSD1306_SETDISPLAYOFFSET,
	0x00,
	SSD1306_SETSTARTLINE,
	SSD1306_CHARGEPUMP,
	0x14,
	SSD1306_MEMORYMODE,
	0x00,
	SSD1306_SEGREMAP | 0x1,
	SSD1306_COMSCANDEC,
	SSD1306_SETCOMPINS,
	0x12,
	SSD1306_SETCONTRAST,
	0xCF,
	SSD1306_SETPRECHARGE,
	0xF1,
	SSD1306_SETVCOMDETECT,
	0x40,
	SSD1306_DISPLAYALLON_RESUME,
	SSD1306_NORMALDISPLAY,
	SSD1306_DISPLAYON
};

static void
ssd1306_init(int width, int height)
{
	unsigned int i;

	g_ssd1306_width = width;
	g_ssd1306_height = height;
	g_ssd1306_buffer = calloc(1, width * height / 8);

	for(i = 0; i < ARRAY_SIZE(ssd1306_init_data); i++) {
		ssd1306_send_command(ssd1306_init_data[i]);
	}
}

void
ssd1306_invert(uint8_t inverted) {
	if (inverted) {
		ssd1306_send_command(SSD1306_INVERTDISPLAY);
	} else {
		ssd1306_send_command(SSD1306_NORMALDISPLAY);
	}
}

static void
ssd1306_draw_pixel(int x, int y, uint32_t color)
{
	uint8_t shift = y % 8;

	if (color)
		g_ssd1306_buffer[x + (y / 8) * g_ssd1306_width] |= (1 << shift);
	else
		g_ssd1306_buffer[x + (y / 8) * g_ssd1306_width] &= ~(1 << shift);
}

static const uint8_t ssd1306_pre_send_buffer_data[] = {
	SSD1306_COLUMNADDR,
	0x00,
	0x7F,
	SSD1306_PAGEADDR,
	0x00,
	0x07,
};


// Pass 8-bit (each) R,G,B, get back 16-bit packed color
static uint32_t
ssd1306_color_from_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (r || g || b);
}


static void
ssd1306_display()
{
	uint8_t packet;
	uint8_t send_val[17] = {0x40};	
	unsigned int i;

	for(i = 0; i < ARRAY_SIZE(ssd1306_pre_send_buffer_data); i++) {
		ssd1306_send_command(ssd1306_pre_send_buffer_data[i]);
	}

	// We have to send the buffer as 16 bytes packets
	// Our buffer is 1024 bytes long, 1024/16 = 64
	// We have to send 64 packets
	for (packet = 0; packet < 64; packet++) {
		memcpy(&send_val[1], &g_ssd1306_buffer[packet*16], 16);
		i2c_bus_write(g_ssd1306_i2c, g_ssd1306_address, send_val, 17);
	}
}

static void
ssd1306_parse_json(json_value *disp_data)
{
        unsigned int i, length;
	json_value *value;
	const char *name;

	length = disp_data->u.object.length;
	for (i = 0; i < length; i++) {
		value = disp_data->u.object.values[i].value;
		name = disp_data->u.object.values[i].name;

		if (strcmp(name, "addr") == 0) {
			g_ssd1306_address = strtol(value->u.string.ptr, NULL, 16);
		} else if (strcmp(name, "i2c") == 0) {
			g_ssd1306_i2c = i2c_bus_get_by_name(value->u.string.ptr);
		}
	}
	PANIC_ON(g_ssd1306_address == 0 || g_ssd1306_i2c == NULL,
			"Missing ssd1306 info\n");
}

display_ops_t ssd1306_display_ops = {
	.name = "ssd1306",
	.init = ssd1306_init,
	.draw_pixel = ssd1306_draw_pixel,
	.fill_rect = NULL,
	.color_from_rgb = ssd1306_color_from_rgb,
	.disp = ssd1306_display,
	.parse_json = ssd1306_parse_json,
};

