#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <inttypes.h>

typedef struct display_ops {
	const char *name;
	void (*init)(const char *str, int width, int height);
	void (*draw_pixel)(int x, int y, uint8_t value);
	void (*disp)(void);
} display_ops_t;

void
display_init();

#endif
