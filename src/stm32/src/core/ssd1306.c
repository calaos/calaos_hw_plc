#include <stdint.h>
#include <stdlib.h>
#include "ssd1306.h"
#include "utils.h"
#include "HAL.h"

static uint8_t g_ssd1306_address;

void
ssd1306_send_command(uint8_t command)
{
	uint8_t cmd[2] = {0x00, command};

	hal_i2c_start(NULL);
	hal_i2c_write(NULL, g_ssd1306_address, cmd, 2);
	hal_i2c_stop(NULL);
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

void
ssd1306_init(uint8_t address)
{
	unsigned int i;
	g_ssd1306_address = address;
	//~ i2c.init(SSD1306_DEFAULT_ADDRESS);

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

static const uint8_t ssd1306_pre_send_buffer_data[] = {
	SSD1306_COLUMNADDR,
	0x00,
	0x7F,
	SSD1306_PAGEADDR,
	0x00,
	0x07,
};

void ssd1306_sendFramebuffer(uint8_t *buffer)
{
	uint8_t packet;
	const uint8_t pre_byte_val = 0x40;	
	unsigned int i;

	for(i = 0; i < ARRAY_SIZE(ssd1306_pre_send_buffer_data); i++) {
		ssd1306_send_command(ssd1306_pre_send_buffer_data[i]);
	}

	// We have to send the buffer as 16 bytes packets
	// Our buffer is 1024 bytes long, 1024/16 = 64
	// We have to send 64 packets
	for (packet = 0; packet < 64; packet++) {
		hal_i2c_start(NULL);
		hal_i2c_write(NULL, g_ssd1306_address, &pre_byte_val, 1);
		hal_i2c_write(NULL, g_ssd1306_address, &buffer[packet*16], 16);
		hal_i2c_stop(NULL);
	}
}
