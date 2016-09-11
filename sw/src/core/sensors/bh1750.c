#include <string.h>

#include "sensors.h"
#include "bh1750.h"
#include "utils.h"
#include "debug.h"
#include "json.h"
#include "i2c.h"

//~ #define BH1750_I2CADDR 0x23

// No active state
#define BH1750_POWER_DOWN 0x00

// Wating for measurment command
#define BH1750_POWER_ON 0x01

// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET 0x07

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE  0x10

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE_2  0x11

// Start measurement at 4lx resolution. Measurement time is approx 16ms.
#define BH1750_CONTINUOUS_LOW_RES_MODE  0x13

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE  0x20

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE_2  0x21

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_LOW_RES_MODE  0x23


typedef struct bh1750_sensor {
	sensor_t *light_sensor;
	uint8_t addr;
	i2c_bus_t *i2c;
	uint16_t max_value;
	uint16_t min_value;
	uint8_t autolevel;
	unsigned long long refresh_time;
	unsigned long long last_refresh;

	SLIST_ENTRY(bh1750_sensor) link;
} bh1750_sensor_t;

SLIST_HEAD(, bh1750_sensor) g_bh1750_list = SLIST_HEAD_INITIALIZER(g_bh1750_list);

static int
bh1750_configure(bh1750_sensor_t *bh1750, uint8_t mode)
{
	uint8_t value;

	if (i2c_bus_read(bh1750->i2c, bh1750->addr, &value, 1) != 0) {
		dbg_log("bh1750 with address 0x%x did not answer, freeing\n", bh1750->addr);
		return 1;
	}
	
	switch (mode) {
		case BH1750_CONTINUOUS_HIGH_RES_MODE:
		case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
		case BH1750_CONTINUOUS_LOW_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE:
		case BH1750_ONE_TIME_HIGH_RES_MODE_2:
		case BH1750_ONE_TIME_LOW_RES_MODE:
			i2c_bus_write(bh1750->i2c, bh1750->addr, &mode, 1);
			ms_delay(10);
		break;
		default:
			return 1;
		break;
	}
	
	return 0;
}


uint16_t bh1750_read(bh1750_sensor_t *bh1750) {

	uint16_t level;
  
	i2c_bus_read(bh1750->i2c, bh1750->addr, (uint8_t *) &level, 2);

	/* convert to lux */
	level /= 1.2;

	dbg_log("Light level: %d\n", level);

	return level;
}

static void
bh1750_poll_one(bh1750_sensor_t *bh1750)
{
	sensor_value_t light;
	uint16_t val;

	unsigned long long time = hal_get_milli();
	if ((time - bh1750->last_refresh) < bh1750->refresh_time)
		return;

	bh1750->last_refresh =time;

	val = bh1750_read(bh1750);
	
	if (bh1750->autolevel) {
		if (val > bh1750->max_value)
			bh1750->max_value = val;
		if (val < bh1750->min_value)
			bh1750->min_value = val;
	}
	
	

	light.val_i = (val - bh1750->min_value)  * 100 / (bh1750->max_value - bh1750->min_value);

	sensors_sensor_update(bh1750->light_sensor, light);
}

static void
bh1750_poll()
{
	bh1750_sensor_t *bh1750;

	SLIST_FOREACH(bh1750, &g_bh1750_list, link) {
		bh1750_poll_one(bh1750);
	}
}


static const sensors_ops_t bh1750_ops =
{
	.set = NULL,
	.req = NULL,
};


static int
bh1750_json_parse_one(json_value* section)
{
	int length, i, id = 0;
	json_value *value;
	const char *name;
	bh1750_sensor_t *bh1750;

	bh1750 = calloc(1, sizeof(bh1750_sensor_t));
	PANIC_ON(!bh1750, "Alloc failed");
	/* Default maximum value */
	bh1750->max_value = (uint16_t) -1;
	bh1750->min_value = 0;

        length = section->u.object.length;
        for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;

		if (strcmp(name, "addr") == 0) {
			bh1750->addr = strtol(value->u.string.ptr, NULL, 16);
		} else if (strcmp(name, "i2c") == 0) {
			bh1750->i2c = i2c_bus_get_by_name(value->u.string.ptr);
		} else if (strcmp(name, "refresh") == 0) {
			bh1750->refresh_time = value->u.integer;
		} else if (strcmp(name, "id") == 0) {
			id = value->u.integer;
		} else if (strcmp(name, "max") == 0) {
			bh1750->max_value = value->u.integer;
		} else if (strcmp(name, "min") == 0) {
			bh1750->min_value = value->u.integer;
		} else if (strcmp(name, "auto") == 0) {
			bh1750->autolevel = value->u.integer;
		}
        }
        
        if (bh1750->autolevel) {
		bh1750->max_value = 0;
		bh1750->min_value = (uint16_t) -1;
		dbg_log("Using autolevel for bh1750 \n");
	}

        if (bh1750_configure(bh1750, BH1750_CONTINUOUS_HIGH_RES_MODE)) {
		free(bh1750);
		return 1;
	}

	SLIST_INSERT_HEAD(&g_bh1750_list, bh1750, link);

	bh1750->light_sensor = sensor_create(SENSORS_TYPE_LIGHT, "bh1750", id, &bh1750_ops, bh1750);

	return 0;
}

static int
bh1750_json_parse(json_value* section)
{
	unsigned int i;

	if (section->type != json_array)
		return 1;

	for (i = 0; i < section->u.array.length; i++) {
		bh1750_json_parse_one(section->u.array.values[i]);
	}

	return 0;
}


static sensor_handler_t bh1750_sensor_handler = {
	.name = "bh1750",
	.json_parse = bh1750_json_parse,
	.poll = bh1750_poll,
};

void
bh1750_init()
{
	sensors_register_handler(&bh1750_sensor_handler);
}

