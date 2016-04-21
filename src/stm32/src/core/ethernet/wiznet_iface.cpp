#include "WIZnetInterface.h"
#include "wiznet_iface.h"

/**
 * WIZnetUInteface wrapping
 */

extern "C" {

wiznet_iface_t *wiznet_iface_create(gen_io_t *cs, gen_io_t *reset)
{
	return reinterpret_cast<wiznet_iface_t *>( new WIZnetInterface(cs, reset) );
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

wiznet_udp_t *wiznet_udp_create()
{
	return reinterpret_cast<wiznet_udp_t *>(new UDPSocket());
}

int wiznet_udp_bind(wiznet_udp_t *udp, int port)
{
	return reinterpret_cast<UDPSocket*>(udp)->bind(port);
}

int wiznet_udp_send_to(wiznet_udp_t *udp, wiznet_ep_t *ep, char *packet, int length)
{
	Endpoint *ep_obj = reinterpret_cast<Endpoint*>(ep);

	return reinterpret_cast<UDPSocket*>(udp)->sendTo(*ep_obj, packet, length);
}

int wiznet_udp_recv_from(wiznet_udp_t *udp, wiznet_ep_t *ep, char *buffer, int length)
{
	Endpoint *ep_obj = reinterpret_cast<Endpoint*>(ep);

	return reinterpret_cast<UDPSocket*>(udp)->receiveFrom(*ep_obj, buffer, length);
}

}
