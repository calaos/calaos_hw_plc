#include "HAL.h"
#include "gpio.h"
#include "debug.h"
#include "utils.h"
#include "module.h"
#include "mysensor.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct mysensor_sensor_ops {
	/**
	 * Function call in main loop
	 */
	void (* poll)(mysensor_sensor_t *);
	/**
	 * Function call when set is received from controller
	 */
	void (* set)(mysensor_sensor_t *, int subtype, const char *payload);
	/**
	 * Function call when request is received from controller
	 */
	void (* req)(mysensor_sensor_t *, int subtype, const char *payload);
} mysensor_sensor_ops_t;

/**
 * S_LIGHT specific data
 */
typedef struct mysensor_s_light{
	hal_gpio_t *io;
	int last_state;
} mysensor_s_light_t;

/**
 * Sensor struct
 */
typedef struct mysensor_sensor {
	char name[MYSENSOR_MAX_NAME_LENGTH];
	unsigned int id;
        mysensor_sensortype_t type;
	const mysensor_sensor_ops_t *ops;
        union {
		mysensor_s_light_t s_light;
	} _;
} mysensor_sensor_t;


#define MAX_SENSOR_COUNT	255

/**
 * Node id requested from controller
 */
static unsigned char g_assigned_node_id = 0;

static const mysensor_sensor_ops_t* g_sensor_ops[];

/**
 * Sensor management
 */
static unsigned char g_max_sensor_id = 0;
static mysensor_sensor_t *g_sensors[MAX_SENSOR_COUNT];

static const char *sensor_type_str[] = {
    [0] = "S_DOOR",                 // Door and window sensors
    [1] = "S_MOTION",               // Motion sensors
    [2] = "S_SMOKE",                // Smoke sensor
    [3] = "S_LIGHT",                // Light Actuator (on/off)
    [4] = "S_DIMMER",               // Dimmable device of some kind
    [5] = "S_COVER",                // Window covers or shades
    [6] = "S_TEMP",                 // Temperature sensor
    [7] = "S_HUM",                  // Humidity sensor
    [8] = "S_BARO",                 // Barometer sensor (Pressure)
    [9] = "S_WIND",                 // Wind sensor
    [10] = "S_RAIN",                // Rain sensor
    [11] = "S_UV",                  // UV sensor
    [12] = "S_WEIGHT",              // Weight sensor for scales etc.
    [13] = "S_POWER",               // Power measuring device, like power meters
    [14] = "S_HEATER",              // Heater device
    [15] = "S_DISTANCE",            // Distance sensor
    [16] = "S_LIGHT_LEVEL",         // Light sensor
    [17] = "S_ARDUINO_NODE",        // Arduino node device
    [18] = "S_ARDUINO_RELAY",       // Arduino relaying node device
    [19] = "S_LOCK",                // Lock device
    [20] = "S_IR",                  // Ir sender/receiver device
    [21] = "S_WATER",               // Water meter
    [22] = "S_AIR_QUALITY",         // Air quality sensor e.g. MQ-2
    [23] = "S_CUSTOM",              // Use this for custom sensors where no other fits.
    [24] = "S_DUST",                // Dust level sensor
    [25] = "S_SCENE_CONTROLLER",    // Scene controller device
};

static int
mysensor_typestr_to_type(const char *name)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(sensor_type_str); i++) {
		if (strcmp(sensor_type_str[i], name) == 0) {
			return i;
		}
	}

	return -1;
}


static char g_mysensor_str[MYSENSOR_MAX_MSG_LENGTH];
static unsigned char g_str_cur_index = 0;

static int mysensor_serial_get_message(char *str)
{
	int ret;
	char c;

	ret = hal_serial_getc(&c);
	if (ret == 0)
		return 0;

	if (c == '\n') {
		g_mysensor_str[g_str_cur_index] = '\0';
		g_str_cur_index = 0;
		strcpy(str, g_mysensor_str);
		debug_puts("Got mysensor query: %s\n", g_mysensor_str);
		return 1;
	}

	g_mysensor_str[g_str_cur_index++] = c;
	if (g_str_cur_index == MYSENSOR_MAX_MSG_LENGTH) {
		debug_puts("Received string too long from controller, discarding\r\n");
		g_str_cur_index = 0;
	}

	return 0;
}


static int mysensor_split_message(char *str, char *split_str[6])
{
	int i;
	char *next = str;

	for (i = 0; i < 6; i++) {
		split_str[i] = next;
		if (i == 5)
			break;

		next = strchr(next, ';');
		if (next == NULL)
			return 1;
		*next = '\0';
		next++;
	}

	return 0;
}

static int mysensor_handle_serial()
{
	char query[MYSENSOR_MAX_MSG_LENGTH];
	unsigned char child_sensor_id, message_type, ack, subtype;
	char *split_str[6], *payload;
	mysensor_sensor_t *sensor;

	/* Check for serial message */
	if (!mysensor_serial_get_message(query))
		return 0;

	if (mysensor_split_message(query, split_str) != 0)
		return 0;

	if (atoi(split_str[0]) != g_assigned_node_id)
		return 0;

	child_sensor_id = atoi(split_str[1]);
	if (g_sensors[child_sensor_id] == NULL)
		return 0;

	sensor = g_sensors[child_sensor_id];

	message_type = atoi(split_str[2]);
	ack = atoi(split_str[3]);
	subtype = atoi(split_str[4]);
	payload = split_str[5];
	
	switch (message_type) {
		case SET_VARIABLE:
			sensor->ops->set(sensor, subtype, payload);
		break;
		case REQUEST_VARIABLE:
			sensor->ops->req(sensor, subtype, payload);
		break;
	};
	
	if (ack) {
		debug_puts("Ack requested\r\n");
	}

	return 1;
}

/**
 * FIXME: generate these functions
 */
static int
mysensor_send_message_str(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, char *payload)
{
	char msg[MYSENSOR_MAX_MSG_LENGTH];
	sprintf(msg, "%d;%d;%d;%d;%d;%s\n", node_id, child_sensor_id, message_type, ack, sub_type, payload);
	return hal_serial_puts(msg);
}

static int
mysensor_send_message_float(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, float value)
{
	char msg[MYSENSOR_MAX_MSG_LENGTH];
	sprintf(msg, "%d;%d;%d;%d;%d;%f\n", node_id, child_sensor_id, message_type, ack, sub_type, value);
	return hal_serial_puts(msg);
}

static int
mysensor_send_message_int(uint16_t node_id, uint8_t child_sensor_id, uint16_t message_type,
				uint8_t ack, uint16_t sub_type, int value)
{
	char msg[MYSENSOR_MAX_MSG_LENGTH];
	sprintf(msg, "%d;%d;%d;%d;%d;%d\n", node_id, child_sensor_id, message_type, ack, sub_type, value);
	return hal_serial_puts(msg);
}

__unused__ static int
mysensor_update_value_float(mysensor_sensor_t *s, mysensor_datatype_t dt, float value)
{
	return mysensor_send_message_float(g_assigned_node_id, s->id, SET_VARIABLE, REQUEST, dt, value);
}

static int
mysensor_update_value_int(mysensor_sensor_t *s, mysensor_datatype_t dt, int value)
{
	return mysensor_send_message_int(g_assigned_node_id, s->id, SET_VARIABLE, REQUEST, dt, value);
}

__unused__ static int
mysensor_update_value_str(mysensor_sensor_t *s, mysensor_datatype_t dt, char *str)
{
	return mysensor_send_message_str(g_assigned_node_id, s->id, SET_VARIABLE, REQUEST, dt, str);
}

static mysensor_sensor_t *
mysensor_create_sensor(mysensor_sensortype_t type, const char *name, unsigned char id)
{
	mysensor_sensor_t *s;

	if (g_sensors[id] != NULL)
		return NULL;

	s = calloc(1, sizeof(*s));
	if (!s)
		return NULL;

	strncpy(s->name, name, MYSENSOR_MAX_NAME_LENGTH);
	s->id = id;
	s->type = type;
	s->ops = g_sensor_ops[type];
	mysensor_send_message_str(g_assigned_node_id, s->id, PRESENTATION, REQUEST, s->type, s->name);
	g_sensors[id] = s;

	if (id > g_max_sensor_id)
		g_max_sensor_id = id;

	return s;
}


static int
mysensor_json_parse_sensor(json_value* sensor)
{
	int length, i;
	const char *name;
	char s_name[MYSENSOR_MAX_NAME_LENGTH], s_gpio_name[MYSENSOR_MAX_NAME_LENGTH];
	unsigned char s_id = 0;
	int s_gpio_dir = GPIO_DIR_OUTPUT, s_reverse = 0, s_type = -1;
	json_value *value;
	mysensor_sensor_t *s;
	
        length = sensor->u.object.length;
        for (i = 0; i < length; i++) {
		value = sensor->u.object.values[i].value;
		name = sensor->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			strcpy(s_name, value->u.string.ptr);
		} else if (strcmp(name, "gpio") == 0) {
			strcpy(s_gpio_name, value->u.string.ptr);
		} else if (strcmp(name, "direction") == 0) {
			if (strcmp(value->u.string.ptr, "input") == 0)
				s_gpio_dir = GPIO_DIR_INPUT;
		} else if (strcmp(name, "type") == 0) {
			s_type = mysensor_typestr_to_type(value->u.string.ptr);
		} else if (strcmp(name, "reverse") == 0) {
			s_reverse = value->u.boolean;
		} else if (strcmp(name, "id") == 0) {
			s_id = value->u.integer;
		}
        }

	/* TODO: Check parameters */
	s = mysensor_create_sensor(s_type, s_name, s_id);
	/* TODO: per type parser */
	s->_.s_light.io = hal_gpio_setup(s_gpio_name, s_reverse, s_gpio_dir);

	return 0;
}

static int
mysensor_json_parse_sensors(json_value* section)
{
	unsigned int i, j;
	json_value* entry;
	json_value* sensor;
	if (section == NULL || section->type != json_object)
		return -1;

	debug_puts("Got mysensors section\r\n");

        for (i = 0; i < section->u.object.length; i++) {
		entry = section->u.object.values[i].value;
		if (strcmp(section->u.object.values[i].name, "sensors") == 0) {
			for (j = 0; j < entry->u.array.length; j++) {
				sensor = entry->u.array.values[j];
				mysensor_json_parse_sensor(sensor);
			}
		} else if (strcmp(section->u.object.values[i].name, "node_id") == 0) {
			g_assigned_node_id = entry->u.integer;
			debug_puts("Node id: %d\n", g_assigned_node_id);
		}
        }

	return 0;
}

static int
mysensor_json_parse(json_value* value)
{
        int length, i;
	if (value == NULL || value->type != json_object) {
                return -1;
        }
     
        length = value->u.object.length;
        for (i = 0; i < length; i++) {
		/* We only care about sensor section*/
		if (strcmp(value->u.object.values[i].name, "mysensors") != 0)
			continue;

		mysensor_json_parse_sensors(value->u.object.values[i].value);
		
        }

	if (g_assigned_node_id == 0) {
		mysensor_send_message_str(0, 0, INTERNAL, REQUEST, 0, "1.0");
		/* Wait message */
		g_assigned_node_id = 1;
	}

        return -1;
}



static void
mysensor_main_loop()
{
	unsigned int i;

	mysensor_handle_serial();

	for (i = 0; i < g_max_sensor_id; i++) {
		if (g_sensors[i] == NULL)
			continue;

		mysensor_sensor_t *sensor = g_sensors[i];
		if (sensor->ops->poll)
			sensor->ops->poll(sensor);
	}
}

/**
 *  Light
 */
static void
s_light_poll(mysensor_sensor_t * sensor)
{
	mysensor_s_light_t  *light = &sensor->_.s_light;
	int state = hal_gpio_read(light->io);

	if (state != light->last_state) {
		light->last_state = state;
		mysensor_update_value_int(sensor, V_STATUS, state);
	}
}

static void
s_light_set(mysensor_sensor_t * sensor, __unused__ int subtype, const char *payload)
{
	mysensor_s_light_t  *light = &sensor->_.s_light;
	int state;
	if (hal_gpio_get_dir(light->io) != GPIO_DIR_OUTPUT)
		return;
	
	state = atoi(payload);
	hal_gpio_write(light->io, state);
}

mysensor_sensor_ops_t s_light_ops =
{
	.poll = s_light_poll,
	.set = s_light_set,
	.req = NULL,
};

static const mysensor_sensor_ops_t* g_sensor_ops[] = {
    [S_DOOR] = NULL,
    [S_MOTION] = NULL,
    [S_SMOKE] = NULL,
    [S_LIGHT] = &s_light_ops,
    [S_DIMMER] = NULL,
    [S_COVER] = NULL,
    [S_TEMP] = NULL,
    [S_HUM] = NULL,
    [S_BARO] = NULL,
    [S_WIND] = NULL,
    [S_RAIN] = NULL,
    [S_UV] = NULL,
    [S_WEIGHT] = NULL,
    [S_POWER] = NULL,
    [S_HEATER] = NULL,
    [S_DISTANCE] = NULL,
    [S_LIGHT_LEVEL] = NULL,
    [S_ARDUINO_NODE] = NULL,
    [S_ARDUINO_RELAY] = NULL,
    [S_LOCK] = NULL,
    [S_IR] = NULL,
    [S_WATER] = NULL,
    [S_AIR_QUALITY] = NULL,
    [S_CUSTOM] = NULL,
    [S_DUST] = NULL,
    [S_SCENE_CONTROLLER] = NULL,
};


const module_t mysensor_module = {
	.name = "mysensor",
	.main_loop = mysensor_main_loop,
	.json_parse = mysensor_json_parse,
};

void
mysensor_init()
{
	module_register(&mysensor_module);


}
