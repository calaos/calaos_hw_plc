#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ili9341.h"
#include "generic_io.h"
#include "utils.h"
#include "HAL.h"

static uint32_t g_ili9341_width, g_ili9341_height;
static gen_io_t *g_ili9341_cs = NULL, *g_ili9341_dc = NULL, *g_ili9341_rst = NULL;

static void
ili9341_send(int dc, uint8_t value)
{   
    /* register or data */
    gen_io_write(g_ili9341_dc, dc);

    /* transmit via SPI */
    gen_io_write(g_ili9341_cs, 0);
    hal_spi_write(value);
    gen_io_write(g_ili9341_cs, 1);
}

struct ili9341_command {
	char type;
	char value;
};

static const struct ili9341_command ili9341_init_cmds[] =
{
	{ILI9341_REG,  0xCB},
	{ILI9341_DATA, 0x39},
	{ILI9341_DATA, 0x2C},
	{ILI9341_DATA, 0x00},
	{ILI9341_DATA, 0x34},
	{ILI9341_DATA, 0x02},

	{ILI9341_REG,  0xCF},
	{ILI9341_DATA, 0x00},
	{ILI9341_DATA, 0XC1},
	{ILI9341_DATA, 0X30},

	{ILI9341_REG,  0xE8},
	{ILI9341_DATA, 0x85},
	{ILI9341_DATA, 0x00},
	{ILI9341_DATA, 0x78},

	{ILI9341_REG,  0xEA},
	{ILI9341_DATA, 0x00},
	{ILI9341_DATA, 0x00},

	{ILI9341_REG,  0xED},
	{ILI9341_DATA, 0x64},
	{ILI9341_DATA, 0x03},
	{ILI9341_DATA, 0X12},
	{ILI9341_DATA, 0X81},

	{ILI9341_REG,  0xF7},
	{ILI9341_DATA, 0x20},

	{ILI9341_REG,  0xC0}, // Power control
	{ILI9341_DATA, 0x23}, // VRH[5:0]

	{ILI9341_REG,  0xC1}, // Power control
	{ILI9341_DATA, 0x10}, // SAP[2:0];BT[3:0]

	{ILI9341_REG,  0xC5}, // VCM control
	{ILI9341_DATA, 0x3e},
	{ILI9341_DATA, 0x28},

	{ILI9341_REG,  0xC7}, // VCM control2
	{ILI9341_DATA, 0x86},

	{ILI9341_REG,  0x36}, // Memory Access Control
	{ILI9341_DATA, 0x88}, // C8

	{ILI9341_REG,  0x3A},
	{ILI9341_DATA, 0x55},

	{ILI9341_REG,  0xB1},
	{ILI9341_DATA, 0x00},
	{ILI9341_DATA, 0x18},

	{ILI9341_REG,  0xB6}, // Display Function Control
	{ILI9341_DATA, 0x08},
	{ILI9341_DATA, 0x82},
	{ILI9341_DATA, 0x27},

	{ILI9341_REG,  0xF2}, // 3Gamma Function Disable
	{ILI9341_DATA, 0x00},

	{ILI9341_REG,  0x26}, // Gamma curve selected
	{ILI9341_DATA, 0x01},

	{ILI9341_REG,  0xE0}, // Set Gamma
	{ILI9341_DATA, 0x0F},
	{ILI9341_DATA, 0x31},
	{ILI9341_DATA, 0x2B},
	{ILI9341_DATA, 0x0C},
	{ILI9341_DATA, 0x0E},
	{ILI9341_DATA, 0x08},
	{ILI9341_DATA, 0x4E},
	{ILI9341_DATA, 0xF1},
	{ILI9341_DATA, 0x37},
	{ILI9341_DATA, 0x07},
	{ILI9341_DATA, 0x10},
	{ILI9341_DATA, 0x03},
	{ILI9341_DATA, 0x0E},
	{ILI9341_DATA, 0x09},
	{ILI9341_DATA, 0x00},

	{ILI9341_REG,  0xE1}, // Set Gamma
	{ILI9341_DATA, 0x00},
	{ILI9341_DATA, 0x0E},
	{ILI9341_DATA, 0x14},
	{ILI9341_DATA, 0x03},
	{ILI9341_DATA, 0x11},
	{ILI9341_DATA, 0x07},
	{ILI9341_DATA, 0x31},
	{ILI9341_DATA, 0xC1},
	{ILI9341_DATA, 0x48},
	{ILI9341_DATA, 0x08},
	{ILI9341_DATA, 0x0F},
	{ILI9341_DATA, 0x0C},
	{ILI9341_DATA, 0x31},
	{ILI9341_DATA, 0x36},
	{ILI9341_DATA, 0x0F},

	{ILI9341_REG,  0x11}, // Sleep out
};
	
static void
ili9341_init(int width, int height)
{
	g_ili9341_width = width;
	g_ili9341_height = height;
	unsigned int i;

	if (g_ili9341_rst != NULL) {
		gen_io_write(g_ili9341_rst, 1);
		ms_delay(5);
		gen_io_write(g_ili9341_rst, 0);
		ms_delay(20);
		gen_io_write(g_ili9341_rst, 1);
		ms_delay(150);
	}

	for (i = 0; i < ARRAY_SIZE(ili9341_init_cmds); i++) {
		ili9341_send(ili9341_init_cmds[i].type, ili9341_init_cmds[i].value); 
	}

	ms_delay(120);

	ili9341_send(ILI9341_REG, 0x2c);

	//lcd_fill(global_bg_color);
    
	ili9341_send(ILI9341_REG, 0x29); // Display on 
	ili9341_send(ILI9341_REG, 0x2c);
}

static void
ili9341_set_cursor_x(uint16_t x)
{
	if (x >= g_ili9341_width)
		return;
    
	ili9341_send(ILI9341_REG, 0x2B);
	ili9341_send(ILI9341_DATA, x >> 8);
	ili9341_send(ILI9341_DATA, x & 0xFF);
	ili9341_send(ILI9341_REG, 0x2c);
}

static void
ili9341_set_cursor_y(uint16_t y)
{
	if (y >= g_ili9341_height)
		return;

	ili9341_send(ILI9341_REG, 0x2A);
	ili9341_send(ILI9341_DATA, y >> 8);
	ili9341_send(ILI9341_DATA, y & 0xFF);
	ili9341_send(ILI9341_REG, 0x2c);
}

static void
ili9341_set_cursor(uint16_t x, uint16_t y)
{
	ili9341_set_cursor_x(x);
	ili9341_set_cursor_y(y);
}

static void
ili9341_send_pixel(uint16_t color)
{
    ili9341_send(ILI9341_DATA, color >> 8);
    ili9341_send(ILI9341_DATA, color & 0xFF);
}

static void
ili9341_draw_pixel(int x, int y, uint16_t color)
{
	ili9341_set_cursor(x, y);
	ili9341_send_pixel(color);
}

static void
ili9341_display()
{
}

static void
ili9341_parse_json(json_value *disp_data)
{
        unsigned int i, length;
	json_value *value;
	const char *name;

	length = disp_data->u.object.length;
	for (i = 0; i < length; i++) {
		value = disp_data->u.object.values[i].value;
		name = disp_data->u.object.values[i].name;

		if (strcmp(name, "cs") == 0) {
			g_ili9341_cs = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "dc") == 0) {
			g_ili9341_dc = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "rst") == 0) {
			g_ili9341_rst = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		}
	}
	PANIC_ON(g_ili9341_cs == NULL, "Missing io for screen cs\r\n");
	PANIC_ON(g_ili9341_dc == NULL, "Missing io for screen dc\r\n");

	/* Deselect cs */
	gen_io_write(g_ili9341_cs, 1);
}

display_ops_t ili9341_display_ops = {
	.name = "ili9341",
	.init = ili9341_init,
	.draw_pixel = ili9341_draw_pixel,
	.disp = ili9341_display,
	.parse_json = ili9341_parse_json,
};

