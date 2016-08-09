#include "WIZnetInterface.h"
#include "wiznet_iface.h"

/**
 * WIZnetUInteface wrapping
 */

extern "C" {

wiznet_iface_t *wiznet_iface_create(spi_bus_t *spi, gen_io_t *cs, gen_io_t *reset)
{
	return reinterpret_cast<wiznet_iface_t *>( new WIZnetInterface(spi, cs, reset) );
}

void wiznet_iface_destroy(wiznet_iface_t *iface)
{
	delete reinterpret_cast<WIZnetInterface*>(iface);
}

int wiznet_iface_init_dhcp(wiznet_iface_t *iface, uint8_t * mac)
{
	return reinterpret_cast<WIZnetInterface*>(iface)->init(mac);
}

int wiznet_iface_init_static(wiznet_iface_t *iface, uint8_t * mac, const char* ip, const char* mask, const char* gateway)
{
	return reinterpret_cast<WIZnetInterface*>(iface)->init(mac, ip, mask, gateway);
}

int wiznet_iface_connect(wiznet_iface_t *iface)
{
	return reinterpret_cast<WIZnetInterface*>(iface)->connect();
}

int wiznet_iface_disconnect(wiznet_iface_t *iface)
{
	return reinterpret_cast<WIZnetInterface*>(iface)->disconnect();
}

char* wiznet_iface_get_ip(wiznet_iface_t *iface)
{
	return reinterpret_cast<WIZnetInterface*>(iface)->getIPAddress();
}

char* wiznet_iface_get_netmask(wiznet_iface_t *iface)
{
	return reinterpret_cast<WIZnetInterface*>(iface)->getNetworkMask();
}

char* wiznet_iface_get_gateway(wiznet_iface_t *iface)
{
	return reinterpret_cast<WIZnetInterface*>(iface)->getGateway();
}

char* wiznet_iface_get_mac(wiznet_iface_t *iface)
{
	return reinterpret_cast<WIZnetInterface*>(iface)->getMACAddress();
}

/**
 * Endpoint wrapping
 */
wiznet_ep_t *wiznet_ep_create()
{
	return reinterpret_cast<wiznet_ep_t *>( new Endpoint() );
}

void wiznet_ep_destroy(wiznet_ep_t *ep)
{
	delete reinterpret_cast<Endpoint*>(ep);
}

void wiznet_ep_reset_address(wiznet_ep_t *ep)
{
	return reinterpret_cast<Endpoint*>(ep)->reset_address();
}

int  wiznet_ep_set_address(wiznet_ep_t *ep, const char* host, const int port)
{
	return reinterpret_cast<Endpoint*>(ep)->set_address(host, port);
}
    
char* wiznet_ep_get_address(wiznet_ep_t *ep)
{
	return reinterpret_cast<Endpoint*>(ep)->get_address();
}

int wiznet_ep_get_port(wiznet_ep_t *ep)
{
	return reinterpret_cast<Endpoint*>(ep)->get_port();
}


/**
 * UDP socket Wrapping
 */

wiznet_udp_sock_t *wiznet_udp_sock_create()
{
	return reinterpret_cast<wiznet_udp_sock_t *>(new UDPSocket());
}

int wiznet_udp_sock_init(wiznet_udp_sock_t *udp)
{
	return reinterpret_cast<UDPSocket*>(udp)->init();
}

void wiznet_udp_sock_set_blocking(wiznet_udp_sock_t *udp, bool blocking, int timeout)
{
	reinterpret_cast<UDPSocket*>(udp)->set_blocking(blocking, timeout);
}

int wiznet_udp_sock_bind(wiznet_udp_sock_t *udp, int port)
{
	return reinterpret_cast<UDPSocket*>(udp)->bind(port);
}

int wiznet_udp_sock_send_to(wiznet_udp_sock_t *udp, wiznet_ep_t *ep, char *packet, int length)
{
	Endpoint *ep_obj = reinterpret_cast<Endpoint*>(ep);

	return reinterpret_cast<UDPSocket*>(udp)->sendTo(*ep_obj, packet, length);
}

int wiznet_udp_sock_recv_from(wiznet_udp_sock_t *udp, wiznet_ep_t *ep, char *buffer, int length)
{
	Endpoint *ep_obj = reinterpret_cast<Endpoint*>(ep);

	return reinterpret_cast<UDPSocket*>(udp)->receiveFrom(*ep_obj, buffer, length);
}

/**
 * TCP socket Wrapping
 */

wiznet_tcp_server_t *wiznet_tcp_server_create()
{
	return reinterpret_cast<wiznet_tcp_server_t *>(new TCPSocketServer());
}

int wiznet_tcp_server_bind(wiznet_tcp_server_t *serv, int port)
{
	return reinterpret_cast<TCPSocketServer*>(serv)->bind(port);
}

int wiznet_tcp_server_listen(wiznet_tcp_server_t *serv, int backlog)
{

	return reinterpret_cast<TCPSocketServer*>(serv)->listen(backlog);
}

int wiznet_tcp_server_accept(wiznet_tcp_server_t *serv, wiznet_tcp_sock_t *sock)
{
	TCPSocketConnection *sock_obj = reinterpret_cast<TCPSocketConnection*>(sock);

	return reinterpret_cast<TCPSocketServer*>(serv)->accept(*sock_obj);
}

void wiznet_tcp_server_set_blocking(wiznet_tcp_server_t *serv, bool blocking, int timeout)
{
	reinterpret_cast<TCPSocketServer*>(serv)->set_blocking(blocking, timeout);
}

wiznet_tcp_sock_t *wiznet_tcp_sock_create()
{
	return reinterpret_cast<wiznet_tcp_sock_t *>(new TCPSocketConnection());
}

int wiznet_tcp_sock_connect(wiznet_tcp_sock_t *sock, const char* host, const int port)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->connect(host, port);
}

bool wiznet_tcp_sock_is_connected(wiznet_tcp_sock_t *sock)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->is_connected();
}

bool wiznet_tcp_sock_is_fin_received(wiznet_tcp_sock_t *sock)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->is_fin_received();
}

int wiznet_tcp_sock_send(wiznet_tcp_sock_t *sock, char* data, int length)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->send(data, length);
}

int wiznet_tcp_sock_send_all(wiznet_tcp_sock_t *sock, char* data, int length)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->send_all(data, length);
}

int wiznet_tcp_sock_receive(wiznet_tcp_sock_t *sock, char* data, int length)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->receive(data, length);
}

int wiznet_tcp_sock_receive_all(wiznet_tcp_sock_t *sock, char* data, int length)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->receive_all(data, length);
}

void wiznet_tcp_sock_set_blocking(wiznet_tcp_sock_t *sock, bool blocking, int timeout)
{
	reinterpret_cast<TCPSocketConnection*>(sock)->set_blocking(blocking, timeout);
}

void wiznet_tcp_sock_close(wiznet_tcp_sock_t *sock)
{
	reinterpret_cast<TCPSocketConnection*>(sock)->close();	
}

char* wiznet_tcp_sock_get_address(wiznet_tcp_sock_t *sock)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->get_address();
}

int wiznet_tcp_sock_get_port(wiznet_tcp_sock_t *sock)
{
	return reinterpret_cast<TCPSocketConnection*>(sock)->get_port();
}

}
