#include <SoftwareSerial.h>
#include <CalaosPLCBusProtocol.h>

#include "crc16.h"

#define DE_PIN		12
#define PLC_BUS_RX	10
#define PLC_BUS_TX	11

#define NODE_SLAVE_ID	12
#define NODE_NAME	"test"

SoftwareSerial plc_bus(PLC_BUS_RX, PLC_BUS_TX);
uint8_t buffer[CPBP_MAX_MESSAGE_SIZE];

void setup()
{
	plc_bus.begin(115200);
}

int wait_message(uint16_t &type)
{
	struct cpbp_msg_header *hdr;
	uint16_t len = 0, *expected_crc16;

	if (!plc_bus.available())
		return;

	/* Ok, we have data, start accumulating */
	unsigned long start = micros();

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

	if (crc16(0, in_buffer, len - CPBP_CRC_SIZE - 1) != *expected_crc16)
		return CALAOS_PLC_BUS_CRC_ERR;

	if (hdr->slave_id != NODE_SLAVE_ID)
		return CALAOS_PLC_BUS_SLAVE_ERR;
}


void loop ()
{
	wait_message();

}
