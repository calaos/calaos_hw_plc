#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <inttypes.h>

#include "config.h"

typedef struct display_ops {
	const char *name;
	void (*init)(int width, int height);
	void (*draw_pixel)(int x, int y, uint8_t value);
	void (*disp)(void);
	void (*parse_json)(json_value *value);
} display_ops_t;

void
display_init();

#endif
