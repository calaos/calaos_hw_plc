#ifndef CALAOSPLCBUSPROTOCOL_H
#define CALAOSPLCBUSPROTOCOL_H

#define CALAOS_BUS_CAP_INPUT		(1 << 0)
#define CALAOS_BUS_CAP_OUTPUT		(1 << 1)
#define CALAOS_BUS_CAP_TEMP		(1 << 2)
#define CALAOS_BUS_CAP_HUMID		(1 << 3)

enum calaos_plc_bus_protocol_req_type {
	CALAOS_PLC_BUS_REQ_DISCOVER = 0,
};


struct calaos_plc_bus_protocol_req {
	uint16_t cap_count;
};
	
struct calaos_plc_bus_protocol_cap {
	uint8_t cap;
	uint8_t count;
};

#endif
