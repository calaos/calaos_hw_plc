#include "CalaosPLCBusNode.h"
#include <string.h>

CalaosPLCBusNode::CalaosPLCBusNode(char node_name[CPBP_MAX_NODE_NAME_LEN], uint16_t node_id)
{
	id = node_id;
	memcpy(name, name, CPBP_MAX_NODE_NAME_LEN);
}
