#include <SoftwareSerial.h>
#include <CalaosPLCBusProtocol.h>

#include "crc16.h"

#define DE_PIN		12
#define PLC_BUS_RX	10
#define PLC_BUS_TX	11

SoftwareSerial plc_bus(PLC_BUS_RX, PLC_BUS_TX);
uint8_t buffer[CPBP_MAX_MESSAGE_SIZE];

void setup()
{
	plc_bus.begin(115200);
}

int wait_message()
{
	struct cpbp_msg_header *hdr;
	uint16_t len;

	while (!available) {
		/* FIXME, we should sleep while nothing to do
		 * some sort of deep sleep wake on interrupt could be nice */
	}

	/* Ok, we have data, start accumulating */
	unsigned long start = micros();

	while (1) {
		/* We encountered the inter frame silence */
		if ((micros() - start) > CPBP_INTER_FRAME_SILENCE_USEC)
			break;

		
	}
	
}


void loop ()
{
	receive_message();

}
