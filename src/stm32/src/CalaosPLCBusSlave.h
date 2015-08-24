#ifndef CALAOSPLCBUSSLAVE_H
#define CALAOSPLCBUSSLAVE_H

#include <string> 

class CalaosPLCBusSlave {
private:
	uint16_t slave_id;
	string name;
	uint32_t capabilities;
public:
	CalaosPLCBusSlave(uint16_t slave_id, uint32_t capabilities): slave_id(slave_id), capabilities(capabilities) {};
	~CalaosPLCBusSlave() {};

	bool has_capability(uint32_t cap) { return (capabilities & cap);};
	void set_capabilities(uint32_t capabilities) {capabilities = capabilities;};
	uint32_t get_capabilities() {return capabilities;};

	void set_name(string name) {name = name;};
	string get_name() {return name;};

	void set_slave_id(uint16_t slave_id) {slave_id = slave_id;};
	uint16_t get_slave_id() {return slave_id;};

};

#endif
