#include "mbed_util.h"

extern "C" {
#include "debug.h"
}

PinName
mbed_pinname_from_str(const char *gpio_name)
{
	PinName name;
	int port_num, gpio_num;

	if (gpio_name[0] != 'P')
		return NC;

	if (gpio_name[2] != '_')
		return NC;

	port_num = gpio_name[1] - 'A';
	gpio_num = atoi(&gpio_name[3]);

	dbg_log("Opening port %d, gpio %d\n", port_num, gpio_num);

	name = (PinName) ((port_num << 4) | gpio_num);

	return name;
}
