#ifndef CALAOSPLCBUSPROTOCOL_H
#define CALAOSPLCBUSPROTOCOL_H

enum cpbp_cap_type{
	CALAOS_BUS_CAP_INPUT = 0,
	CALAOS_BUS_CAP_OUTPUT = 1,
	CALAOS_BUS_CAP_TEMP = 2,
	CALAOS_BUS_CAP_HUMID = 3,
};

/**
 * List of requests type
 */
enum cpbp_req_type {
	CALAOS_PLC_BUS_REQ_DISCOVER = 0,
};

/**
 * First header sent by node after in answer to discover
 */
struct cpbp_req {
	uint16_t cap_count;	/**< Count of capabilities descriptors in response */
};

/**
 * Struct located after discover to parse
 */
struct cpbp_cap_desc {
	uint8_t type;		/**< Capability type */
	uint8_t count;		/**< Count of such capability */
};

#endif
