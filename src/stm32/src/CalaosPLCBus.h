#ifndef CALAOSPLCBUS_H
#define CALAOSPLCBUS_H

#include <mbed.h>
#include <RawSerial.h>

#include <list>

#include "CalaosPLCBusSlave.h"
#include "CalaosPLCBusProtocol.h"

#define MAX_SLAVE_NODES			128

class CalaosPLCBus {
private:
	RawSerial bus_serial;
	DigitalOut de;
	uint8_t in_buffer[CPBP_MAX_MESSAGE_SIZE];
	list<CalaosPLCBusSlave *> slaves;

	int read_single_message(uint16_t slave_id, uint16_t request_type, void *buf, uint16_t buf_len, uint16_t *read_len);
	int write_message(uint16_t slave_id, uint16_t request_type, uint8_t *buf, uint16_t len);
	int read_message(uint16_t slave_id, uint16_t request_type, void *buf, uint16_t buf_len, uint16_t *read_len);
	int parse_discover(CalaosPLCBusSlave *slave, uint8_t *buffer);
public:
	/**
	 * Create a new 
	 * @return -1
	 */
	CalaosPLCBus(PinName tx, PinName rx, PinName de) : bus_serial(tx, rx), de(de) {};
	~CalaosPLCBus() {};

	int discover();
};

#endif
