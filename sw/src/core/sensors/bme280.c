#define _GNU_SOURCE 1

#include "bme280.h"
#include "module.h"
#include "utils.h"
#include "debug.h"
#include "json.h"
#include "i2c.h"

#include <string.h>
#include <stdlib.h>

#define BME180_CHIPID	0x60

typedef struct bme280 {
	uint8_t addr;
	i2c_bus_t *i2c;
	unsigned long long refresh_time;
	unsigned long long last_refresh;

	/* Compensation parameters */
	uint16_t dig_T1;
	int16_t dig_T2, dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
	uint16_t dig_H1, dig_H3;
	int16_t dig_H2, dig_H4, dig_H5, dig_H6;
	int32_t t_fine;
	
} bme280_t;

static bme280_t bme280_s;

static int bme280_init_hardware()
{
	uint8_t cmd[18];
	
	cmd[0] = 0xD0;
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, cmd, 1);
	i2c_bus_read(bme280_s.i2c, bme280_s.addr, cmd, 1);
	
	if (cmd[0] != BME180_CHIPID) {
		debug_puts("Device is not a BME180\r\n");
		return 1;
	}

	cmd[0] = 0xf2; // ctrl_hum
	cmd[1] = 0x01; // Humidity oversampling x1
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, cmd, 2);

	cmd[0] = 0xf4; // ctrl_meas
	cmd[1] = 0x27; // Temparature oversampling x1, Pressure oversampling x1, Normal mode
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, cmd, 2);

	cmd[0] = 0xf5; // config
	cmd[1] = 0x80; // Standby 500ms, Filter off
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, cmd, 2);

	cmd[0] = 0x88; // read dig_T regs
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, cmd, 1);
	i2c_bus_read(bme280_s.i2c, bme280_s.addr, cmd, 6);

	bme280_s.dig_T1 = (cmd[1] << 8) | cmd[0];
	bme280_s.dig_T2 = (cmd[3] << 8) | cmd[2];
	bme280_s.dig_T3 = (cmd[5] << 8) | cmd[4];

	cmd[0] = 0x8E; // read dig_P regs
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, cmd, 1);
	i2c_bus_read(bme280_s.i2c, bme280_s.addr, cmd, 18);

	bme280_s.dig_P1 = (cmd[ 1] << 8) | cmd[ 0];
	bme280_s.dig_P2 = (cmd[ 3] << 8) | cmd[ 2];
	bme280_s.dig_P3 = (cmd[ 5] << 8) | cmd[ 4];
	bme280_s.dig_P4 = (cmd[ 7] << 8) | cmd[ 6];
	bme280_s.dig_P5 = (cmd[ 9] << 8) | cmd[ 8];
	bme280_s.dig_P6 = (cmd[11] << 8) | cmd[10];
	bme280_s.dig_P7 = (cmd[13] << 8) | cmd[12];
	bme280_s.dig_P8 = (cmd[15] << 8) | cmd[14];
	bme280_s.dig_P9 = (cmd[17] << 8) | cmd[16];

	cmd[0] = 0xA1; // read dig_H regs
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, cmd, 1);
	i2c_bus_read(bme280_s.i2c, bme280_s.addr, cmd, 1);
	cmd[1] = 0xE1; // read dig_H regs
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, &cmd[1], 1);
	i2c_bus_read(bme280_s.i2c, bme280_s.addr, &cmd[1], 7);

	bme280_s.dig_H1 = cmd[0];
	bme280_s.dig_H2 = (cmd[2] << 8) | cmd[1];
	bme280_s.dig_H3 = cmd[3];
	bme280_s.dig_H4 = (cmd[4] << 4) | (cmd[5] & 0x0f);
	bme280_s.dig_H5 = (cmd[6] << 4) | ((cmd[5]>>4) & 0x0f);
	bme280_s.dig_H6 = cmd[7];
	
	return 0;
}

static int
bme280_json_parse(json_value* section)
{
	int length, i;
	json_value *value;
	const char *name;

	memset(&bme280_s, 0, sizeof(bme280_s));

        length = section->u.object.length;
        for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;

		if (strcmp(name, "addr") == 0) {
			bme280_s.addr = strtol(value->u.string.ptr, NULL, 16);
		} else if (strcmp(name, "i2c") == 0) {
			bme280_s.i2c = i2c_bus_get_by_name(value->u.string.ptr);
		} else if (strcmp(name, "refresh") == 0) {
			bme280_s.refresh_time = value->u.integer;
		}
        }

	return bme280_init_hardware();
}


static float
bme280_get_temp(uint32_t temp_raw)
{
	float tempf;
	int32_t temp;

	temp =
	(((((temp_raw >> 3) - (bme280_s.dig_T1 << 1))) * bme280_s.dig_T2) >> 11) +
	((((((temp_raw >> 4) - bme280_s.dig_T1) * ((temp_raw >> 4) - bme280_s.dig_T1)) >> 12) * bme280_s.dig_T3) >> 14);

	bme280_s.t_fine = temp;
	temp = (temp * 5 + 128) >> 8;
	tempf = (float)temp;

	return (tempf/100.0f);
}
 
static float
bme280_get_pressure(uint32_t press_raw)
{
	float pressf;
	int32_t var1, var2;
	uint32_t press;

	var1 = (bme280_s.t_fine >> 1) - 64000;
	var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * bme280_s.dig_P6;
	var2 = var2 + ((var1 * bme280_s.dig_P5) << 1);
	var2 = (var2 >> 2) + (bme280_s.dig_P4 << 16);
	var1 = (((bme280_s.dig_P3 * (((var1 >> 2)*(var1 >> 2)) >> 13)) >> 3) + ((bme280_s.dig_P2 * var1) >> 1)) >> 18;
	var1 = ((32768 + var1) * bme280_s.dig_P1) >> 15;
	if (var1 == 0) {
		return 0;
	}
	press = (((1048576 - press_raw) - (var2 >> 12))) * 3125;
	if(press < 0x80000000) {
		press = (press << 1) / var1;
	} else {
		press = (press / var1) * 2;
	}

	var1 = ((int32_t)bme280_s.dig_P9 * ((int32_t)(((press >> 3) * (press >> 3)) >> 13))) >> 12;
	var2 = (((int32_t)(press >> 2)) * (int32_t)bme280_s.dig_P8) >> 13;
	press = (press + ((var1 + var2 + bme280_s.dig_P7) >> 4));

	pressf = (float)press;
	return (pressf/100.0f);
}

static float
bme280_get_humidity(uint32_t hum_raw)
{
	float humf;
	int32_t v_x1;

	v_x1 = bme280_s.t_fine - 76800;
	v_x1 =  (((((hum_raw << 14) -(((int32_t)bme280_s.dig_H4) << 20) - (((int32_t)bme280_s.dig_H5) * v_x1)) +
	       ((int32_t)16384)) >> 15) * (((((((v_x1 * (int32_t)bme280_s.dig_H6) >> 10) *
					    (((v_x1 * ((int32_t)bme280_s.dig_H3)) >> 11) + 32768)) >> 10) + 2097152) *
					    (int32_t)bme280_s.dig_H2 + 8192) >> 14));
	v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * (int32_t)bme280_s.dig_H1) >> 4));
	v_x1 = (v_x1 < 0 ? 0 : v_x1);
	v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);

	humf = (float)(v_x1 >> 12);

	return (humf/1024.0f);
}

void
bme280_main_loop()
{
	uint8_t samples[8];
	uint32_t press_raw, temp_raw, hum_raw;
	float temp, hum, press;

	unsigned long long time = hal_get_milli();
	if ((time - bme280_s.last_refresh) < bme280_s.refresh_time)
		return;

	bme280_s.last_refresh =	time;

	/* Read the whole temp + humid + pressure in one burst */
	samples[0] = 0xF7;
	i2c_bus_write(bme280_s.i2c, bme280_s.addr, samples, 1);
	i2c_bus_read(bme280_s.i2c, bme280_s.addr, samples, 8);

	press_raw = (samples[0] << 12) | (samples[1] << 4) | (samples[2] >> 4);
	temp_raw = (samples[3] << 12) | (samples[4] << 4) | (samples[5] >> 4);
	hum_raw = (samples[6] << 8) | samples[7];
	
	temp = bme280_get_temp(temp_raw);
	hum = bme280_get_humidity(hum_raw);
	press = bme280_get_pressure(press_raw);

	debug_puts("temp: %f, humidity: %f, pressure:%f\r\n", temp, hum, press);
}


/**
 * Module
 */
static const module_t bme280_module = {
	.name = "bme280",
	.main_loop = bme280_main_loop,
	.json_parse = bme280_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};


void
bme280_init()
{
	module_register(&bme280_module);
}
