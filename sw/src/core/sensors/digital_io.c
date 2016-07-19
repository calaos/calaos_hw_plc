#include "json.h"
#include "utils.h"
#include "module.h"
#include "sensors.h"

#include <string.h>

/**
 * dioitch specific data
 */
typedef struct sensor_dio {
	gen_io_t *io;
	sensor_t *s;
	SLIST_ENTRY(sensor_dio) link;
} digital_io_t;

static void
digital_io_set(sensor_t * sensor, void *data, sensor_value_t value)
{
	digital_io_t *dio = data;
	int state;
	if (gen_io_get_dir(dio->io) != GPIO_DIR_OUTPUT)
		return;

	state = value.val_i;
	gen_io_write(dio->io, state);
}

static void
digital_io_req(sensor_t * sensor, void *data, sensor_value_t *value)
{
	digital_io_t *dio = data;
	if (gen_io_get_dir(dio->io) != GPIO_DIR_INPUT)
		return;

	value->val_i = gen_io_read(dio->io);
}

static const sensors_ops_t digital_io_ops =
{
	.set = digital_io_set,
	.req = digital_io_req,
};

void digital_io_watcher_cb(gen_io_t *io, int value, void * data)
{
	sensor_value_t val = {.val_i = value};
	digital_io_t *dio = data;

	sensors_sensor_update(dio->s, val);
}

static int
digital_io_json_parse_one(json_value* sensor)
{
	int length, i;
	const char *name;
	const char *s_name = NULL, *s_gpio_name = NULL;
	unsigned char s_id = 0;
	int s_gpio_dir = GPIO_DIR_OUTPUT, s_reverse = 0;
	gpio_debounce_t s_debounce = GPIO_DEBOUNCE_DISABLE;
	json_value *value;
	digital_io_t *dio;
	char c_mode;
	gpio_pin_mode_t s_mode = GPIO_MODE_PULL_NONE;
	
	dio = malloc(sizeof(digital_io_t));
	PANIC_ON(!dio, "Alloc failed");

        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			s_name = value->u.string.ptr;
		} else if (strcmp(name, "io") == 0) {
			s_gpio_name = value->u.string.ptr;
		} else if (strcmp(name, "dir") == 0) {
			if (strcmp(value->u.string.ptr, "in") == 0)
				s_gpio_dir = GPIO_DIR_INPUT;
		} else if (strcmp(name, "active_low") == 0) {
			s_reverse = value->u.integer;
		} else if (strcmp(name, "id") == 0) {
			s_id = value->u.integer;
		} else if (strcmp(name, "debounce") == 0) {
			s_debounce = value->u.integer;
		} else if (strcmp(name, "mode") == 0) {
			c_mode = value->u.string.ptr[0];
			switch (c_mode) {
				case 'v': s_mode = GPIO_MODE_PULL_DOWN; break;
				case '^': s_mode = GPIO_MODE_PULL_UP; break;
				case 'o': s_mode = GPIO_MODE_OPEN_DRAIN; break;
			}
		}
        }

        PANIC_ON(s_name == NULL || s_gpio_name == NULL,
			"Incomplete sensor description");
	dio->io = gen_io_setup(s_gpio_name, s_reverse, s_gpio_dir, s_debounce, s_mode);
	dio->s = sensor_create(SENSORS_TYPE_SWITCH, s_name, s_id, &digital_io_ops, dio);

	gen_io_add_watcher(dio->io, digital_io_watcher_cb, dio);

	return 0;
}



static int
digital_io_json_parse(json_value* section)
{
        unsigned int i;

	for (i = 0; i < section->u.array.length; i++) {
		digital_io_json_parse_one(section->u.array.values[i]);
	}

	return 0;
}


/**
 * Module
 */
static sensor_handler_t digital_io_sensor_handler = {
	.name = "digital_io",
	.json_parse = digital_io_json_parse,
	.poll = NULL,
};

void
digital_io_init()
{
	sensors_register_handler(&digital_io_sensor_handler);
}
