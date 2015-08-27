#ifndef CALAOSBUS_H
#define CALAOSBUS_H


#include "CalaosPLCBusProtocol.h"
#include "CalaosPLCBusNode.h"
#include <SoftwareSerial.h>

class CalaosBus {
private:
	uint8_t buffer[CPBP_MAX_MESSAGE_SIZE];
	SoftwareSerial plc_bus;
	int de_pin;
	CalaosPLCBusNode node;
public:
	CalaosBus(int tx_pin, int rx_pin, int de_pin, CalaosPLCBusNode node);
	void set_bus_speed(int speed);
	int get_message();
};

#endif
