#include "wiznet_iface.h"
#include "network.h"
#include "module.h"
#include "utils.h"

#include <string.h>

static wiznet_iface_t *g_net_iface;
static wiznet_udp_t *g_udp_port;
static uint8_t g_mac[6];

static void
network_main_loop(void)
{
	
}

static int
network_init_interface(gen_io_t *cs, gen_io_t *rst)
{
	int ret;

	g_net_iface = wiznet_iface_create(cs, rst);
	PANIC_ON(!g_net_iface, "Failed create network interface\r\n");
	
	ret = wiznet_iface_init_dhcp(g_net_iface, g_mac);
	PANIC_ON(ret, "Failed to init network\r\n");
		
	ret = wiznet_iface_connect(g_net_iface);
	PANIC_ON(ret, "Failed to obtain ip through DHCP\r\n");
	
	g_udp_port = wiznet_udp_create();
	PANIC_ON(!g_udp_port, "Failed create network interface\r\n");

	ret = wiznet_udp_init(g_udp_port);
	PANIC_ON(ret, "Failed init UDP interface\r\n");

	ret = wiznet_udp_bind(g_udp_port, 14987);
	PANIC_ON(ret, "Failed to listen to UDP interface\r\n");

	return 0;
}

static int
network_set_mac(const char *mac)
{
	long int macc;
	int i;

	for (i = 0; i < 6; i++) {
		macc = strtol(&mac[i * 3], NULL, 16);
		g_mac[i] = macc;
	}

	debug_puts("Read mac %02X:%02X:%02X:%02X:%02X:%02X\r\n",
		g_mac[0],g_mac[1],g_mac[2],g_mac[3],g_mac[4],g_mac[5]);
		
	return 0;
}

static int
wiznet_parse_json(json_value* net_data)
{
        unsigned int i, length;
	json_value *value;
	const char *name;
	int frequency = 1000000;
	gen_io_t *cs = NULL, *rst = NULL;

	length = net_data->u.object.length;
	for (i = 0; i < length; i++) {
		value = net_data->u.object.values[i].value;
		name = net_data->u.object.values[i].name;

		if (strcmp(name, "cs") == 0) {
			cs = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "rst") == 0) {
			rst = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		} else if (strcmp(name, "freq") == 0) {
			frequency = value->u.integer;
		}
	}
	PANIC_ON(cs == NULL, "Missing io for screen cs\r\n");
	PANIC_ON(rst == NULL, "Missing io for screen rst\r\n");
	hal_spi_init(frequency);

	return network_init_interface(cs, rst);
}

static int
network_json_parse(json_value* value)
{
        unsigned int i, length;
	json_value *section, __unused__ *data = NULL;
	char *name;
	__unused__ const char *type = NULL;

	section = config_get_section(value, "net");
	if (!section)
		return -1;

	length = section->u.object.length;
	for (i = 0; i < length; i++) {
		value = section->u.object.values[i].value;
		name = section->u.object.values[i].name;

		if (strcmp(name, "type") == 0) {
			type = value->u.string.ptr;
		} else if (strcmp(name, "mac") == 0) {
			network_set_mac(value->u.string.ptr);
		}else if (strcmp(name, "data") == 0) {
			data = value;
		}
	}

	return wiznet_parse_json(data);
}


/**
 * Module
 */
static const module_t network_module = {
	.name = "network",
	.main_loop = network_main_loop,
	.json_parse = network_json_parse,
	.sensor_created = NULL,
	.sensor_updated = NULL,
};

void
network_init()
{
	module_register(&network_module);
}
