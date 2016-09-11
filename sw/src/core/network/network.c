#define _GNU_SOURCE 1

#include "wiznet_iface.h"
#include "communication.h"
#include "mysensors.h"
#include "network.h"
#include "module.h"
#include "utils.h"
#include "spi.h"

#include <string.h>

enum default_prot {
	NET_STD_PORT = 13489,
	NET_DBG_PORT,
};

typedef enum network_proto {
	NET_PROTO_UDP = 0,
	NET_PROTO_TCP,
} network_proto_t;

static const char * net_proto_to_str[] = {
	[NET_PROTO_UDP] = "UDP",
	[NET_PROTO_TCP] = "TCP",
};

typedef struct net_if_con {
	uint16_t port;
	/* UDP stuff */
	wiznet_udp_sock_t *udp_sock;
	wiznet_ep_t *recv_ep;
	wiznet_ep_t *send_ep;
	/* TCP stuff */
	wiznet_tcp_server_t *tcp_serv;
	wiznet_tcp_sock_t *tcp_sock;
} net_if_con_t;

static wiznet_iface_t *g_net_iface;

static uint8_t g_mac[6];
static char *g_master_server;

net_if_con_t g_net_con[COM_TYPE_COUNT] = {{.port = NET_STD_PORT}, {.port = NET_DBG_PORT}};
network_proto_t g_net_proto = NET_PROTO_TCP;


static int
network_udp_main_loop(com_type_t com_type, char *buf, unsigned int size)
{
	int ret_size;

	ret_size = wiznet_udp_sock_recv_from(g_net_con[com_type].udp_sock, g_net_con[com_type].recv_ep, buf, MYSENSOR_MAX_MSG_LENGTH);
	if (ret_size < 0)
		return 0;

	return ret_size;
}

static int
network_tcp_main_loop(com_type_t com_type, char *buf, unsigned int size)
{
	net_if_con_t *con = &g_net_con[com_type];
	int ret, ret_size;
	
	if (wiznet_tcp_sock_is_fin_received(con->tcp_sock)){
		dbg_log("Closing socket for com %d\n", com_type);
		wiznet_tcp_sock_close(con->tcp_sock);
	}

	if (!wiznet_tcp_sock_is_connected(con->tcp_sock)) {

		ret = wiznet_tcp_server_accept(con->tcp_serv, con->tcp_sock); 
		if (ret != 0) {
			if (ret == -2) {
				dbg_log("Failed to accept connection: too many socket opened\n");
				wiznet_tcp_sock_close(con->tcp_sock);
			}
			return 0;
		}

		dbg_log("Incoming connection from %s: com %d\n",
			wiznet_tcp_sock_get_address(con->tcp_sock),
			com_type);
	}

	ret_size = wiznet_tcp_sock_receive_all(con->tcp_sock, buf, size);
	if (ret_size < 0)
		return 0; 

	return ret_size;
}

static int (* proto_main_loop[])(com_type_t /* com_type*/, char * /* buf */, unsigned int /* size */) = {
	[NET_PROTO_UDP] = network_udp_main_loop,
	[NET_PROTO_TCP] = network_tcp_main_loop,
};

static void
network_main_loop(void)
{
	char buf[MYSENSOR_MAX_MSG_LENGTH];
	int size;
	com_type_t type = COM_TYPE_STD;
	
	for (type = COM_TYPE_STD; type < COM_TYPE_COUNT; type++) {
		size = proto_main_loop[g_net_proto](type, buf, MYSENSOR_MAX_MSG_LENGTH);
		if (size == 0)
			continue;

		buf[size] = '\0';
		dbg_log("Message received from network type %d\n", type);
		module_handle_message(type, buf, size);
	}
}

static void
network_puts(com_type_t com_type, const char *str)
{
	unsigned int length = strlen(str);

	if (g_net_proto == NET_PROTO_UDP) { 
		wiznet_udp_sock_send_to(g_net_con[com_type].udp_sock, g_net_con[com_type].send_ep, (char *) str, length);
	} else {
		/* Socket is not connected, return */
		if (!wiznet_tcp_sock_is_connected(g_net_con[com_type].tcp_sock))
			return;

		wiznet_tcp_sock_send_all(g_net_con[com_type].tcp_sock, (char *) str, length);
	}
}

static com_handler_t network_com_hdler = {
	.name = "network",
	.put_str = network_puts,
};

static int
network_init_udp_sock(net_if_con_t *con)
{
	int ret;

	con->udp_sock = wiznet_udp_sock_create();
	if(!con->udp_sock) {
		dbg_log("Failed to create network interface");
		return 1;
	}

	ret = wiznet_udp_sock_init(con->udp_sock);
	if(ret) {
		dbg_log("Failed to bind UDP interface");
		return 1;
	}

	wiznet_udp_sock_set_blocking(con->udp_sock, false, 0);

	ret = wiznet_udp_sock_bind(con->udp_sock, con->port);
	if(ret) {
		dbg_log("Failed to listen to UDP interface");
		return 1;
	}

	con->recv_ep = wiznet_ep_create();
	if (!con->recv_ep) {
		dbg_log("Failed create recv endpoint");
		return 1;
	}

	con->send_ep = wiznet_ep_create();
	if (!con->send_ep) {
		dbg_log("Failed create send endpoint");
		return 1;
	}

	ret = wiznet_ep_set_address(con->send_ep, g_master_server, con->port);
	if (ret) {
		dbg_log("Master adress does not exists");
		return 1;
	}

	return 0;
}

static int
network_init_udp_socks()
{
	int i = 0;
	
	for (i = 0; i < COM_TYPE_COUNT; i++) {
		if (network_init_udp_sock(&g_net_con[i])) {
			dbg_puts("Failed to init udp sock %d\n", i);
			return 1;
		}
	}

	return 0;
}


static int
network_init_tcp_sock(net_if_con_t *con)
{
	int ret;

	con->tcp_serv = wiznet_tcp_server_create();
	if(!con->tcp_serv) {
		dbg_log("Failed to create tcp serv");
		return 1;
	}

	ret = wiznet_tcp_server_bind(con->tcp_serv, con->port);
	if(ret) {
		dbg_log("Failed to bind tcp interface");
		return 1;
	}
	
	ret = wiznet_tcp_server_listen(con->tcp_serv, 1);
	if(ret) {
		dbg_log("Failed to set tcp interface to listen");
		return 1;
	}

	wiznet_tcp_server_set_blocking(con->tcp_serv, false, 0);

	con->tcp_sock = wiznet_tcp_sock_create();
	if(!con->tcp_sock) {
		dbg_log("Failed to create tcp socket");
		return 1;
	}

	wiznet_tcp_sock_set_blocking(con->tcp_sock, false, 0);

	return 0;
}


static int
network_init_tcp_socks()
{
	int i = 0;
	
	for (i = 0; i < COM_TYPE_COUNT; i++) {
		if (network_init_tcp_sock(&g_net_con[i])) {
			dbg_puts("Failed to init tcp sock %d\n", i);
			return 1;
		}
	}
	
	return 0;
}

static int
network_init_interface(spi_bus_t *spi, gen_io_t *cs, gen_io_t *rst)
{
	int ret;

	g_net_iface = wiznet_iface_create(spi, cs, rst);
	if (!g_net_iface) {
		dbg_log("Failed create network interface");
		return 1;
	}

	ret = wiznet_iface_init_dhcp(g_net_iface, g_mac);
	if (ret) {
		dbg_log("Failed to init network");
		return 1;
	}

	ret = wiznet_iface_connect(g_net_iface);
	if (ret) {
		dbg_log("Failed to obtain ip through DHCP");
		return 1;
	}
	
	if (g_net_proto == NET_PROTO_UDP) {
		ret = network_init_udp_socks();
	} else {
		ret = network_init_tcp_socks();
	}
	
	if (ret) {
		dbg_log("Failed to init sockets");
		return 1;
	}

	dbg_log("Network initialized: ip %s, listening on port %d, dbg port: %d, type: %s\n",
		wiznet_iface_get_ip(g_net_iface),
		g_net_con[COM_TYPE_STD].port,
		g_net_con[COM_TYPE_DBG].port,
		net_proto_to_str[g_net_proto]);

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

	dbg_log("Read mac %02X:%02X:%02X:%02X:%02X:%02X\n",
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
			"Missing io for network\n");

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
			g_net_con[COM_TYPE_DBG].port = value->u.integer;
		} else if (strcmp(name, "port") == 0) {
			g_net_con[COM_TYPE_STD].port = value->u.integer;
		} else if (strcmp(name, "master") == 0) {
			g_master_server = strdup(value->u.string.ptr);
		} else if (strcmp(name, "proto") == 0) {
			if (strcmp(value->u.string.ptr,"tcp") == 0)
				g_net_proto = NET_PROTO_TCP;
			else if (strcmp(value->u.string.ptr,"udp") == 0)
				g_net_proto = NET_PROTO_UDP;
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
