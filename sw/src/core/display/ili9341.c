#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "generic_io.h"
#include "ili9341.h"
#include "utils.h"
#include "HAL.h"
#include "spi.h"

static uint32_t g_ili9341_width, g_ili9341_height;
static gen_io_t *g_ili9341_cs = NULL, *g_ili9341_dc = NULL, *g_ili9341_rst = NULL;
static spi_bus_t *g_ili9341_spi = NULL;

static void
ili9341_send_reg(uint8_t reg)
{
	/* write register */
	gen_io_write(g_ili9341_dc, ILI9341_REG);
	gen_io_write(g_ili9341_cs, 0);
	spi_bus_write(g_ili9341_spi, reg);
	gen_io_write(g_ili9341_cs, 1);
}

static void
ili9341_send_data(const uint8_t *value, uint8_t size)
{
	unsigned int i;
	/* transmit via SPI */
	gen_io_write(g_ili9341_cs, 0);
	
	gen_io_write(g_ili9341_dc, ILI9341_DATA);    
	for (i = 0; i < size; i++)
		spi_bus_write(g_ili9341_spi, value[i]);

	gen_io_write(g_ili9341_cs, 1);
}

static void
ili9341_send_reg_data(uint8_t reg, const uint8_t *value, uint8_t size)
{
	unsigned int i;
	/* transmit via SPI */
	gen_io_write(g_ili9341_cs, 0);

	gen_io_write(g_ili9341_dc, ILI9341_REG);
	spi_bus_write(g_ili9341_spi, reg);
	
	gen_io_write(g_ili9341_dc, ILI9341_DATA);    
	for (i = 0; i < size; i++)
		spi_bus_write(g_ili9341_spi, value[i]);

	gen_io_write(g_ili9341_cs, 1);
}


static const uint8_t ili9341_init_cmds[] =
{
	3, 0xEF,  0x03, 0x80, 0x02,
	// Power Control B
	3, 0xCF, 0x00, 0XC1, 0X30,
	// Power On sequence control
	4, 0xED, 0x64, 0x03, 0X12, 0X81,
	// Driver timing control A
	3, 0xE8, 0x85, 0x00, 0x78,

	5, 0xCB, 0x39, 0x2C, 0x00, 0x34, 0x02,
 
	1, 0xF7, 0x20,

	2, 0xEA, 0x00, 0x00,
	//VRH[5:0] 
	1, ILI9341_PWCTR1, 0x23, 
	//SAP[2:0];BT[3:0] 
	1, ILI9341_PWCTR2, 0x10,  
	//VCM control
	2, ILI9341_VMCTR1, 0x3e, 0x28,
	//VCM control2 
	1, ILI9341_VMCTR2, 0x86,
	// Memory Access Control 
	1, ILI9341_MADCTL, 0x48,

	1, ILI9341_PIXFMT, 0x55,
  
	2, ILI9341_FRMCTR1, 0x00, 0x18,
	// Display Function Control
	3, ILI9341_DFUNCTR, 0x08, 0x82, 0x27,    
	// 3Gamma Function Disable
	1, 0xF2, 0x00,   
	//Gamma curve selected
	1, ILI9341_GAMMASET, 0x01,
	//Set Gamma 
	15, ILI9341_GMCTRP1, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
	//Set Gamma
	15, ILI9341_GMCTRN1, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,

	0, ILI9341_SLPOUT,   //Exit Sleep 
};

static void
ili9341_fill_rect(int x, int y, int w, int h, uint32_t color);

static void
ili9341_init(int width, int height)
{
	g_ili9341_width = width;
	g_ili9341_height = height;
	unsigned int i = 0;

	if (g_ili9341_rst != NULL) {
		gen_io_write(g_ili9341_rst, 1);
		ms_delay(5);
		gen_io_write(g_ili9341_rst, 0);
		ms_delay(20);
		gen_io_write(g_ili9341_rst, 1);
		ms_delay(150);
	}

	while (i < ARRAY_SIZE(ili9341_init_cmds)) {
		ili9341_send_reg_data(ili9341_init_cmds[i + 1], &ili9341_init_cmds[i + 2], ili9341_init_cmds[i]);
		i += ili9341_init_cmds[i] + 2;
	}

	ms_delay(120);

	ili9341_send_reg(ILI9341_DISPON);   //Display on 
	ili9341_fill_rect(0, 0, width, height, ILI9341_BLACK);
}

static void
ili9341_set_addr_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	uint8_t x_cmd[4] = {x0 >> 8, x0 & 0xFF, x1 >> 8, x1 & 0xFF};
	uint8_t y_cmd[4] = {y0 >> 8, y0 & 0xFF, y1 >> 8, y1 & 0xFF};

	ili9341_send_reg_data(ILI9341_CASET, x_cmd, 4);
	ili9341_send_reg_data(ILI9341_PASET, y_cmd, 4);
	ili9341_send_reg(ILI9341_RAMWR);
}

static void
ili9341_fill_rect(int x, int y, int w, int h, uint32_t color)
{
	uint8_t data[2] = {color >> 8, color & 0xFF};

	ili9341_set_addr_window(x, y, x + w - 1, y + h - 1);

	for(y = h; y > 0; y--) {
		for(x = w; x > 0; x--) {
			ili9341_send_data(data, 2);
		}
	}
}


static void
ili9341_draw_pixel(int x, int y, uint32_t color)
{
	uint8_t data[2] = {color >> 8, color & 0xFF};

	ili9341_set_addr_window(x, y, x+1, y+1);
	ili9341_send_data(data, 2);
}

// Pass 8-bit (each) R,G,B, get back 16-bit packed color
static uint32_t
ili9341_color_from_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

static void
ili9341_display()
{
	/* nothing to do, no framebuffer */
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
			g_ili9341_cs = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "dc") == 0) {
			g_ili9341_dc = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "rst") == 0) {
			g_ili9341_rst = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "spi") == 0) {
			g_ili9341_spi = spi_bus_get_by_name(value->u.string.ptr);
		}
	}
	PANIC_ON(g_ili9341_cs == NULL || g_ili9341_dc == NULL || g_ili9341_spi == NULL,
			"Missing info for screen\n");
	/* Deselect cs */
	gen_io_write(g_ili9341_cs, 1);

	/* Do reset */
	if (g_ili9341_rst != NULL) {
		gen_io_write(g_ili9341_rst, 0);
		ms_delay(100);	
		gen_io_write(g_ili9341_rst, 1);
	}
}

display_ops_t ili9341_display_ops = {
	.name = "ili9341",
	.init = ili9341_init,
	.draw_pixel = ili9341_draw_pixel,
	.fill_rect = ili9341_fill_rect,
	.color_from_rgb = ili9341_color_from_rgb,
	.disp = ili9341_display,
	.parse_json = ili9341_parse_json,
};

