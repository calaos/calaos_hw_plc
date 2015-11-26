#include <stdlib.h>
#include <stdio.h>

#include "pins.h"

struct pin {
	int pin_num;
};

pin_t *
pin_setup(const char *pin_name, int reverse, pin_dir_t direction)
{
	pin_t *pin = malloc(sizeof(struct pin));
	if (pin)
		return NULL;

	pin->pin_num = atoi(pin_name);

	return pin;

}

int
pin_set_state(pin_t *pin, int state)
{
	printf("[PIN] pin %d set to %d\n", pin->pin_num, state);
	return 0;
}

int
pin_get_state(pin_t *pin)
{
	return 0;
}
