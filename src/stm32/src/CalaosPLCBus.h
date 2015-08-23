#ifndef CALAOSPLCBUS_H
#define CALAOSPLCBUS_H

#include <mbed.h>
#include <RawSerial.h>

/* FIXME application dependent */
#define REQUEST_TIMEOUT_MSEC		4

#define INTER_FRAME_SILENCE_USEC	750

#define MAX_MESSAGE_SIZE		1024

#define MAX_BUS_TRIALS			3

enum calaos_plc_bus_err {
	CALAOS_PLC_BUS_WRITE_ERR = 1,
	CALAOS_PLC_BUS_READ_ERR,
	CALAOS_PLC_BUS_TIMEOUT,
	CALAOS_PLC_BUS_CRC_ERR,
};

class CalaosPLCBus {
private:
	RawSerial bus_serial;
	DigitalOut de;
	uint8_t in_buffer[MAX_MESSAGE_SIZE];

	int read_single_message(uint16_t slave_id, void *buf, uint16_t buf_len, uint16_t *read_len);
	
public:
	int write_message(uint16_t slave_id, uint8_t *buf, uint16_t len);
	int read_message(uint16_t slave_id, void *buf, uint16_t buf_len, uint16_t *read_len);
	
	CalaosPLCBus(PinName tx, PinName rx, PinName de) : bus_serial(tx, rx), de(de) {};
	~CalaosPLCBus() {};
};

#endif
