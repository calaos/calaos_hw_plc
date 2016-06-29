#ifndef _NETWORK_H
#define _NETWORK_H

void
network_init();

void
network_send_to_master(uint8_t *buffer, unsigned int length);

#endif
