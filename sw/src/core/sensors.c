#include "json.h"
#include "utils.h"
#include "module.h"
#include "sensors.h"

#include <string.h>

#define SENSOR_MAX_NAME_LENGTH	32
#define MAX_SENSOR_COUNT	64

typedef struct sensors_ops {
	/**
	 * Function call in main loop
	 */
	void (* poll)(sensor_t *);
	/**
	 * Function call when set is received from controller
	 */
	void (* set)(sensor_t *, sensor_value_t value);
	/**
	 * Function call when request is received from controller
	 */
	void (* req)(sensor_t *, sensor_value_t *value);
} sensors_ops_t;


/**
 * switch specific data
 */
typedef struct sensor_switch {
	gen_io_t *io;
	int last_state;
} sensor_switch_t;

/**
 * Sensor struct
 */
typedef struct sensor {
	char name[SENSOR_MAX_NAME_LENGTH];
	unsigned int id;
        union {
		sensor_switch_t sw;
	} _;
        sensors_type_t type;
} sensor_t;


/**
 * Sensor management
 */
static unsigned char g_max_sensor_id = 0;
static sensor_t *g_sensors[MAX_SENSOR_COUNT];

static const sensors_ops_t* g_sensor_ops[];

static const char *sensor_type_str[] = {
    [SENSORS_TYPE_SWITCH] = "switch",
};

static int
sensors_typestr_to_type(const char *name)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(sensor_type_str); i++) {
		if (strcmp(sensor_type_str[i], name) == 0) {
			return i;
		}
	}

	return -1;
}

sensors_type_t
sensor_get_type(sensor_t *s)
{
	return s->type;
}

char *
sensor_get_name(sensor_t *s)
{
	return s->name;
}

int
sensor_get_id(sensor_t *s)
{
	return s->id;
}

sensor_t *
sensors_get_by_id(int id)
{
	if (id > g_max_sensor_id)
		return NULL;

	return g_sensors[id];	
};

static sensor_t *
sensor_create_sensor(sensors_type_t type, const char *name, unsigned char id)
{
	sensor_t *s;

	if (g_sensors[id] != NULL)
		return NULL;

	s = calloc(1, sizeof(*s));
	if (!s)
		return NULL;

	strncpy(s->name, name, SENSOR_MAX_NAME_LENGTH);
	s->id = id;
	s->type = type;
	g_sensors[id] = s;

	module_sensor_created(s);

	if (id > g_max_sensor_id)
		g_max_sensor_id = id;

	return s;
}


static int
sensors_json_parse_sensor(json_value* sensor)
{
	int length, i;
	const char *name;
	const char *s_name = NULL, *s_gpio_name = NULL;
	unsigned char s_id = 0;
	int s_gpio_dir = GPIO_DIR_OUTPUT, s_reverse = 0, s_type = -1;
	gpio_debounce_t s_debounce = GPIO_DEBOUNCE_ENABLE;
	json_value *value;
	sensor_t *s;
	gen_io_t *gpio;
	
        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			s_name = value->u.string.ptr;
		} else if (strcmp(name, "io") == 0) {
			s_gpio_name = value->u.string.ptr;
		} else if (strcmp(name, "dir") == 0) {
			if (strcmp(value->u.string.ptr, "input") == 0)
				s_gpio_dir = GPIO_DIR_INPUT;
		} else if (strcmp(name, "type") == 0) {
			s_type = sensors_typestr_to_type(value->u.string.ptr);
		} else if (strcmp(name, "active_low") == 0) {
			s_reverse = value->u.integer;
		} else if (strcmp(name, "id") == 0) {
			s_id = value->u.integer;
		} else if (strcmp(name, "debounce") == 0) {
			s_debounce = value->u.integer;
		}
        }
        PANIC_ON(s_name == NULL || s_gpio_name == NULL,
			"Incomplete sensor description");
	gpio = gen_io_setup(s_gpio_name, s_reverse, s_gpio_dir, s_debounce);
	/* TODO: Check parameters */
	s = sensor_create_sensor(s_type, s_name, s_id);
	/* TODO: per type parser */
	s->_.sw.io = gpio;

	return 0;
}


static int
sensors_json_parse(json_value* section)
{
        unsigned int i;

	for (i = 0; i < section->u.array.length; i++) {
		sensors_json_parse_sensor(section->u.array.values[i]);
	}

	return 0;
}

static void
sensors_main_loop()
{
	unsigned int i;

	for (i = 0; i < g_max_sensor_id; i++) {
		if (g_sensors[i] == NULL)
			continue;

		sensor_t *s = g_sensors[i];
		if (g_sensor_ops[s->type]->poll)
			g_sensor_ops[s->type]->poll(s);
	}
}


void
sensor_set_value(sensor_t *s, sensor_value_t value)
{
	if (g_sensor_ops[s->type]->set)
		g_sensor_ops[s->type]->set(s, value);
}

void
sensor_get_value(sensor_t *s, sensor_value_t *value)
{
	if (g_sensor_ops[s->type]->req)
		g_sensor_ops[s->type]->req(s, value);
}


/**
 *  Switch
 */
static void
switch_poll(sensor_t * sensor)
{
	sensor_switch_t *sw = &sensor->_.sw;
	sensor_value_t value;
	int state;

	if (gen_io_get_dir(sw->io) != GPIO_DIR_INPUT)
		return;

	state = gen_io_read(sw->io);

	if (state != sw->last_state) {
		sw->last_state = state;
		value.val_i = state;
		module_sensor_updated(sensor, value);
	}
}

static void
switch_set(sensor_t * sensor, sensor_value_t value)
{
	sensor_switch_t *sw = &sensor->_.sw;
	int state;
	if (gen_io_get_dir(sw->io) != GPIO_DIR_OUTPUT)
		return;
	
	state = value.val_i;
	gen_io_write(sw->io, state);
}

sensors_ops_t switch_ops =
{
	.poll = switch_poll,
	.set = switch_set,
	.req = NULL,
};

static const sensors_ops_t* g_sensor_ops[] = {
    [SENSORS_TYPE_SWITCH] = &switch_ops,
};

/**
 * Module
 */
static const module_t sensors_module = {
	.name = "sensors",
	.main_loop = sensors_main_loop,
	.json_parse = sensors_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};

void
sensors_init()
{
	module_register(&sensors_module);
}