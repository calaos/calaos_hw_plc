#include "CalaosBus.h"
#include "crc16.h"
#include <Arduino.h>

#define offsetof(st, m) \
    ((size_t) ( (char *)&((st *)(0))->m - (char *)0 ))
    
CalaosBus::CalaosBus(int tx_pin, int rx_pin, int de_pin, CalaosPLCBusNode node) : 
	plc_bus(rx_pin, tx_pin),
	de_pin(de_pin),
	node(node)
{
	plc_bus.begin(115200);

	pinMode(de_pin, OUTPUT);
	digitalWrite(de_pin, LOW);
};


void CalaosBus::set_bus_speed(int speed)
{
	plc_bus.begin(speed);
}

int CalaosBus::get_message(uint8_t **msg_buffer, uint16_t *msg_len, uint16_t *request_type)
{
	struct cpbp_msg_header *hdr;
	uint16_t len = 0, *expected_crc16;
	unsigned long start;

	if (!plc_bus.available())
		return 0;

	/* Ok, we have data, start accumulating */
	start = micros();

	hdr = (struct cpbp_msg_header *) buffer;
	while (1) {
		/* We encountered the inter frame silence */
		if ((micros() - start) > CPBP_INTER_FRAME_SILENCE_USEC)
			break;

		buffer[len] = Serial.read();
		len++;

		/* Check if we have received the length header */
		if (len >= (offsetof(struct cpbp_msg_header, payload_length) + sizeof(hdr->payload_length)))
			if (len == (sizeof(struct cpbp_msg_header) + hdr->payload_length + CPBP_CRC_SIZE))
				break;
	}

	/* Check the CRC */
	expected_crc16 = (uint16_t *) &buffer[len - CPBP_CRC_SIZE - 1];

	if (crc16(0, buffer, len - CPBP_CRC_SIZE - 1) != *expected_crc16)
		return CALAOS_PLC_BUS_CRC_ERR;

	if (hdr->slave_id != node.get_id())
		return CALAOS_PLC_BUS_SLAVE_ERR;

	*msg_buffer = &buffer[sizeof(struct cpbp_msg_header)];
	*msg_len = hdr->payload_length;
	*request_type = hdr->request_type;

	return 0;
}
