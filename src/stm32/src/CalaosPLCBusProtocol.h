#ifndef CALAOSPLCBUSPROTOCOL_H
#define CALAOSPLCBUSPROTOCOL_H

#include <stdint.h>

/**
 * This depends on how long the node must answer a master request
 */
#define CPBP_REQUEST_TIMEOUT_MSEC	3

/**
 * Minimum time between incoming data to consider two distinct frames
 */
#define CPBP_INTER_FRAME_SILENCE_USEC	750

/**
 * Even if the protocol can make frame up to 65536 btyes, set maximum frame size to a much lower
 * value since microcontroller don't have much memory
 */
#define CPBP_MAX_MESSAGE_SIZE		1024

/**
 * CRC size (crc16)
 */
#define CPBP_CRC_SIZE			2

/**
 * Maximum count of trials for master to send a request
 */
#define CPBP_MAX_BUS_TRIALS		3

/**
 * Maimum length of node name reported for discover
 */
#define CPBP_MAX_NODE_NAME_LEN		10

#define __packed__ __attribute__((packed))


enum cpbp_err {
	CALAOS_PLC_BUS_WRITE_ERR = 1,
	CALAOS_PLC_BUS_READ_ERR,
	CALAOS_PLC_BUS_TIMEOUT,
	CALAOS_PLC_BUS_CRC_ERR,
	CALAOS_PLC_BUS_SLAVE_ERR,
	CALAOS_PLC_BUS_REQUEST_ERR,
};

/**
 * Capabilities
 */
enum cpbp_cap_type{
	CALAOS_BUS_CAP_INPUT = 0,	/**< Node has inputs */
	CALAOS_BUS_CAP_OUTPUT = 1,	/**< Node has outputs */
	CALAOS_BUS_CAP_TEMP = 2,	/**< Node has temperature sensors */
	CALAOS_BUS_CAP_HUMID = 3,	/**< Node has humidity sensors */
};

/**
 * List of requests type
 */
enum cpbp_discover_resp_type {
	CALAOS_PLC_BUS_REQ_DISCOVER = 0,/**< Send a discover request, the slave should answer with a response */
};

/**
 * Message header
 */
struct cpbp_msg_header {
	uint16_t slave_id;		/**< Slave id which should handle the message */
	uint16_t payload_length;	/**< Size of payload */
	uint16_t request_type;		/**< Request type */
} __packed__;

/**
 * First header sent by node after in answer to CALAOS_PLC_BUS_REQ_DISCOVER
 */
struct cpbp_discover_resp {
	const char name[10];	/**< Node name */
	uint16_t cap_count;	/**< Count of capabilities descriptors in response */
} ;

/**
 * Struct located after struct cpbp_discover_resp to describe capabilities
 */
struct cpbp_cap_desc {
	uint8_t type;		/**< Capability type */
	uint8_t count;		/**< Count of such capability */
} __packed__;

#endif
