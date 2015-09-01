#include <SoftwareSerial.h>
#include "CalaosBus.h"
#include "CalaosPLCBusNode.h"

#define DE_PIN		12
#define PLC_BUS_RX	10
#define PLC_BUS_TX	11

#define NODE_SLAVE_ID	12
#define NODE_NAME	"test"

CalaosPLCBusNode node(NODE_NAME, NODE_SLAVE_ID);
CalaosBus plc_bus(PLC_BUS_TX, PLC_BUS_RX, DE_PIN, node);

void setup()
{
}


void loop ()
{
	uint8_t *msg;
	uint16_t msg_len, req_type; 
	int ret;

	ret = plc_bus.get_message(&msg, &msg_len, &req_type);
	if (ret)
		return;

	if (req_type == CALAOS_PLC_BUS_REQ_DISCOVER) {
		
	}
}
