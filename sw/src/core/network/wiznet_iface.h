#ifndef _WIZNET_IFACE_H
#define _WIZNET_IFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "generic_io.h"
#include "spi.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * WIZnetInterface wrapping
 */
typedef struct wiznet_iface wiznet_iface_t;

wiznet_iface_t *wiznet_iface_create(spi_bus_t *spi, gen_io_t *cs, gen_io_t *reset);

void wiznet_iface_destroy(wiznet_iface_t *iface);

int wiznet_iface_init_dhcp(wiznet_iface_t *iface, uint8_t * mac);

int wiznet_iface_init_static(wiznet_iface_t *iface, uint8_t * mac, const char* ip, const char* mask, const char* gateway);

int wiznet_iface_connect(wiznet_iface_t *iface);

int wiznet_iface_disconnect(wiznet_iface_t *iface);

char* wiznet_iface_get_ip(wiznet_iface_t *iface);

char* wiznet_iface_get_netmask(wiznet_iface_t *iface);

char* wiznet_iface_get_gateway(wiznet_iface_t *iface);

char* wiznet_iface_get_mac(wiznet_iface_t *iface);

/**
 * Endpoint wrapping
 */
typedef struct wiznet_ep wiznet_ep_t;

wiznet_ep_t *wiznet_ep_create();

void wiznet_ep_destroy(wiznet_ep_t *ep);

void wiznet_ep_reset_address(wiznet_ep_t *ep);

int  wiznet_ep_set_address(wiznet_ep_t *ep, const char* host, const int port);

char* wiznet_ep_get_address(wiznet_ep_t *ep);

int wiznet_ep_get_port(wiznet_ep_t *ep);

/**
 * UDP socket Wrapping
 */

typedef struct wiznet_udp wiznet_udp_sock_t;

wiznet_udp_sock_t *wiznet_udp_sock_create();

int wiznet_udp_sock_init(wiznet_udp_sock_t *udp);

void wiznet_udp_sock_set_blocking(wiznet_udp_sock_t *udp, bool blocking, int timeout);

int wiznet_udp_sock_bind(wiznet_udp_sock_t *udp, int port);

int wiznet_udp_sock_send_to(wiznet_udp_sock_t *udp, wiznet_ep_t *ep, char *packet, int length);

int wiznet_udp_sock_recv_from(wiznet_udp_sock_t *udp, wiznet_ep_t *ep, char *buffer, int length);

/**
 * TCP socket Wrapping
 */

typedef struct wiznet_tcp_server wiznet_tcp_server_t;

typedef struct wiznet_tcp_sock wiznet_tcp_sock_t;

wiznet_tcp_server_t *wiznet_tcp_server_create();

int wiznet_tcp_server_bind(wiznet_tcp_server_t *serv, int port);

int wiznet_tcp_server_listen(wiznet_tcp_server_t *serv, int backlog);

int wiznet_tcp_server_accept(wiznet_tcp_server_t *serv, wiznet_tcp_sock_t *sock);

void wiznet_tcp_server_set_blocking(wiznet_tcp_server_t *serv, bool blocking, int timeout);


wiznet_tcp_sock_t *wiznet_tcp_sock_create();

int wiznet_tcp_sock_connect(wiznet_tcp_sock_t *sock, const char* host, const int port);

bool wiznet_tcp_sock_is_connected(wiznet_tcp_sock_t *sock);

bool wiznet_tcp_sock_is_fin_received(wiznet_tcp_sock_t *sock);

int wiznet_tcp_sock_send(wiznet_tcp_sock_t *sock, char* data, int length);

int wiznet_tcp_sock_send_all(wiznet_tcp_sock_t *sock, char* data, int length);

int wiznet_tcp_sock_receive(wiznet_tcp_sock_t *sock, char* data, int length);

int wiznet_tcp_sock_receive_all(wiznet_tcp_sock_t *sock, char* data, int length);

void wiznet_tcp_sock_set_blocking(wiznet_tcp_sock_t *sock, bool blocking, int timeout);

void wiznet_tcp_sock_close(wiznet_tcp_sock_t *sock);

char* wiznet_tcp_sock_get_address(wiznet_tcp_sock_t *sock);

int wiznet_tcp_sock_get_port(wiznet_tcp_sock_t *sock);


#ifdef __cplusplus
}
#endif

#endif
