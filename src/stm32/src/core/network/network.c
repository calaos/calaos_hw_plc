#include "wiznet_iface.h"
#include "mysensors.h"
#include "network.h"
#include "module.h"
#include "utils.h"

#include <string.h>

#define DEFAULT_PORT	13489

static wiznet_iface_t *g_net_iface;
static wiznet_udp_t *g_udp_socket;
static uint8_t g_mac[6];
static uint16_t g_port;
static char *g_master_server;

static wiznet_ep_t *g_net_recv_ep, *g_net_send_ep;

static void
network_main_loop(void)
{
	char buf[MYSENSOR_MAX_MSG_LENGTH];
	int size;

	size = wiznet_udp_recv_from(g_udp_socket, g_net_recv_ep, buf, MYSENSOR_MAX_MSG_LENGTH);
	if (size < 0)
		return;

	buf[size] = '\0';
	debug_puts("Parsing message packet received from udp\r\n");
	mysensors_parse_message(buf);
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
	
	g_udp_socket = wiznet_udp_create();
	PANIC_ON(!g_udp_socket, "Failed create network interface\r\n");

	ret = wiznet_udp_init(g_udp_socket);
	PANIC_ON(ret, "Failed init UDP interface\r\n");
	
	wiznet_udp_set_blocking(g_udp_socket, false, 0);

	ret = wiznet_udp_bind(g_udp_socket, g_port);
	PANIC_ON(ret, "Failed to listen to UDP interface\r\n");

	debug_puts("Network initialized: ip %s, listening on udp port %d\r\n",
		wiznet_iface_get_ip(g_net_iface),
		g_port);
		
	g_net_recv_ep = wiznet_ep_create();
	PANIC_ON(!g_net_recv_ep, "Failed create recv endpoint\r\n");

	g_net_send_ep = wiznet_ep_create();
	PANIC_ON(!g_net_send_ep, "Failed create send endpoint\r\n");
	
	ret = wiznet_ep_set_address(g_net_send_ep, g_master_server, g_port);
	PANIC_ON(ret, "Master adress does not exists\r\n");

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
	PANIC_ON(cs == NULL, "Missing io for network cs\r\n");
	PANIC_ON(rst == NULL, "Missing io for network rst\r\n");
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
	int port = DEFAULT_PORT;

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
		} else if (strcmp(name, "data") == 0) {
			data = value;
		} else if (strcmp(name, "port") == 0) {
			port = value->u.integer;
		} else if (strcmp(name, "master") == 0) {
			g_master_server = strdup(value->u.string.ptr);
		}
	}
	
	PANIC_ON(type == NULL, "Network is mandatory");

	g_port = port;

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
