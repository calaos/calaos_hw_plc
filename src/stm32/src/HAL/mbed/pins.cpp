#include <stdlib.h>
#include <mbed.h>

extern "C" {
#include "pins.h"
#include "debug.h"
}

struct pin {
	PinName pin_name;
	DigitalInOut *io;
	int reverse;
};

extern "C"  pin_t *
pin_setup(const char *pin_name, int reverse, pin_dir_t direction)
{
	int port_num, pin_num;
	pin_t *pin = (pin_t *) malloc(sizeof(struct pin));
	if (pin)
		return NULL;

	if (direction == PIN_DIR_OUTPUT)
		pin->io->output();
	else
		pin->io->input();

	if (pin_name[0] != 'P')
		return NULL;

	if (pin_name[2] != '_')
		return NULL;

	port_num = pin_name[1] - 'A';
	pin_num = atoi(&pin_name[3]);

	debug_puts("Opening port %d, pin %d\n", port_num, pin_num);

	pin->pin_name = (PinName) ((port_num << 4) | pin_num);
	pin->io = new DigitalInOut(pin->pin_name);
	pin->reverse = reverse;

	return pin;
}

extern "C" int
pin_set_state(pin_t *pin, int state)
{
	return 0;
}

extern "C" int
pin_get_state(pin_t *pin)
{
	return 0;
}
