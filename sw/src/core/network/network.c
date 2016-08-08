#define _GNU_SOURCE 1

#include "wiznet_iface.h"
#include "communication.h"
#include "mysensors.h"
#include "network.h"
#include "module.h"
#include "utils.h"
#include "spi.h"

#include <string.h>

#define NET_STD_PORT	13489
#define NET_DBG_PORT	(NET_STD_PORT + 1)
#define NET_SHELL_PORT	(NET_SHELL_PORT + 1)

typedef struct net_if_con {
	uint16_t port;
	wiznet_udp_t *sock;
	wiznet_ep_t *recv_ep;
	wiznet_ep_t *send_ep;
} net_if_con_t;


static wiznet_iface_t *g_net_iface;

static uint8_t g_mac[6];
static char *g_master_server;

net_if_con_t std_con = {.port = NET_STD_PORT};
net_if_con_t dbg_con = {.port = NET_DBG_PORT};

static void
network_main_loop(void)
{
	char buf[MYSENSOR_MAX_MSG_LENGTH];
	int size;

	size = wiznet_udp_recv_from(std_con.sock, std_con.recv_ep, buf, MYSENSOR_MAX_MSG_LENGTH);
	if (size < 0)
		return;

	buf[size] = '\0';
	debug_puts("Parsing message packet received from udp\r\n");
	mysensors_parse_message(buf);
}

static void
network_std_puts(const char *str)
{
	unsigned int length = strlen(str);
	wiznet_udp_send_to(std_con.sock, std_con.send_ep, (char *) str, length);
}

static void
network_dbg_puts(const char *str)
{
	unsigned int length = strlen(str);
	wiznet_udp_send_to(dbg_con.sock, dbg_con.send_ep, (char *) str, length);
}

static com_handler_t network_com_hdler = {
	.put_std_str = network_std_puts,
	.put_dbg_str = network_dbg_puts,
};

static int
network_init_sock(net_if_con_t *con)
{
	int ret;

	con->sock = wiznet_udp_create();
	if(!con->sock) {
		debug_puts("Failed to create network interface");
		return 1;
	}

	ret = wiznet_udp_init(con->sock);
	if(ret) {
		debug_puts("Failed to init UDP interface");
		return 1;
	}

	wiznet_udp_set_blocking(con->sock, false, 0);

	ret = wiznet_udp_bind(con->sock, con->port);
	if(ret) {
		debug_puts("Failed to listen to UDP interface");
		return 1;
	}

	con->recv_ep = wiznet_ep_create();
	if (!con->recv_ep) {
		debug_puts("Failed create recv endpoint");
		return 1;
	}

	con->send_ep = wiznet_ep_create();
	if (!con->send_ep) {
		debug_puts("Failed create send endpoint");
		return 1;
	}

	ret = wiznet_ep_set_address(con->send_ep, g_master_server, con->port);
	if (ret) {
		debug_puts("Master adress does not exists");
		return 1;
	}

	return 0;
}

static int
network_init_interface(spi_bus_t *spi, gen_io_t *cs, gen_io_t *rst)
{
	int ret;

	g_net_iface = wiznet_iface_create(spi, cs, rst);
	if (!g_net_iface) {
		debug_puts("Failed create network interface");
		return 1;
	}

	ret = wiznet_iface_init_dhcp(g_net_iface, g_mac);
	if (ret) {
		debug_puts("Failed to init network");
		return 1;
	}

	ret = wiznet_iface_connect(g_net_iface);
	if (ret) {
		debug_puts("Failed to obtain ip through DHCP");
		return 1;
	}

	if (network_init_sock(&std_con)) {
		dbg_puts("Failed to init standard sock\n");
		return 1;
	}

	if (network_init_sock(&dbg_con)) {
		dbg_puts("Failed to init debug sock\n");
		return 1;
	}

	debug_puts("Network initialized: ip %s, listening on udp port %d, dbg port: %d\r\n",
		wiznet_iface_get_ip(g_net_iface),
		std_con.port, dbg_con.port);

	communication_register(&network_com_hdler);

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
		} else if (strcmp(name, "dbg_port") == 0) {
			dbg_con.port = value->u.integer;
		} else if (strcmp(name, "port") == 0) {
			std_con.port = value->u.integer;
		} else if (strcmp(name, "master") == 0) {
			g_master_server = strdup(value->u.string.ptr);
		}
	}
	
	PANIC_ON(type == NULL, "Network is mandatory");

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
