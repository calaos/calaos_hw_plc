#define _GNU_SOURCE 1

#include "wiznet_iface.h"
#include "mysensors.h"
#include "network.h"
#include "module.h"
#include "utils.h"
#include "spi.h"

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

void
network_send_to_master(uint8_t *buffer, unsigned int length)
{
	wiznet_udp_send_to(g_udp_socket, g_net_send_ep, (char *) buffer, length);
}

	void (*put_std_str)(const char *str);
	/**
	 * Output a debug string
	 */
	void (*put_dbg_str)(const char *str);

static int
network_init_interface(spi_bus_t *spi, gen_io_t *cs, gen_io_t *rst)
{
	int ret;

	g_net_iface = wiznet_iface_create(spi, cs, rst);
	PANIC_ON(!g_net_iface, "Failed create network interface");
	
	ret = wiznet_iface_init_dhcp(g_net_iface, g_mac);
	PANIC_ON(ret, "Failed to init network");

	ret = wiznet_iface_connect(g_net_iface);
	PANIC_ON(ret, "Failed to obtain ip through DHCP");
	
	g_udp_socket = wiznet_udp_create();
	PANIC_ON(!g_udp_socket, "Failed create network interface");

	ret = wiznet_udp_init(g_udp_socket);
	PANIC_ON(ret, "Failed init UDP interface");
	
	wiznet_udp_set_blocking(g_udp_socket, false, 0);

	ret = wiznet_udp_bind(g_udp_socket, g_port);
	PANIC_ON(ret, "Failed to listen to UDP interface");

	debug_puts("Network initialized: ip %s, listening on udp port %d\r\n",
		wiznet_iface_get_ip(g_net_iface),
		g_port);

	g_net_recv_ep = wiznet_ep_create();
	PANIC_ON(!g_net_recv_ep, "Failed create recv endpoint");

	g_net_send_ep = wiznet_ep_create();
	PANIC_ON(!g_net_send_ep, "Failed create send endpoint");
	
	ret = wiznet_ep_set_address(g_net_send_ep, g_master_server, g_port);
	PANIC_ON(ret, "Master adress does not exists");

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
	gen_io_t *cs = NULL, *rst = NULL;
	static spi_bus_t *spi_bus = NULL;

	length = net_data->u.object.length;
	for (i = 0; i < length; i++) {
		value = net_data->u.object.values[i].value;
		name = net_data->u.object.values[i].name;

		if (strcmp(name, "cs") == 0) {
			cs = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "rst") == 0) {
			rst = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, GPIO_DEBOUNCE_DISABLE, GPIO_MODE_PULL_NONE);
		} else if (strcmp(name, "spi") == 0) {
			spi_bus = spi_bus_get_by_name(value->u.string.ptr);
		}
	}
	PANIC_ON(cs == NULL || rst == NULL || spi_bus == NULL,
			"Missing io for network\r\n");

	return network_init_interface(spi_bus, cs, rst);
}

static int
network_json_parse(json_value* section)
{
        unsigned int i, length;
	json_value *value, __unused__ *data = NULL;
	char *name;
	__unused__ const char *type = NULL;
	int port = DEFAULT_PORT;

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
};

void
network_init()
{
	module_register(&network_module);
}
