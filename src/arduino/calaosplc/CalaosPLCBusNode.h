#ifndef CALAOSPLCBUSNODE_H
#define CALAOSPLCBUSNODE_H

#include "CalaosPLCBusProtocol.h"

class CalaosPLCBusNode {
private:
	char name[CPBP_MAX_NODE_NAME_LEN];
	uint16_t id;
public:
	CalaosPLCBusNode(char node_name[CPBP_MAX_NODE_NAME_LEN], uint16_t node_id);

	uint16_t get_id() {return id; };
};


#endif
