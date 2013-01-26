#ifndef __COLOR_H__
#define __COLOR_H__

typedef struct color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Color;

int Color_compare(Color *c1, Color *c2);

Color *Color_create(unsigned char r, unsigned char g, unsigned char b);
void Color_free(Color *c);

void Color_printf(Color *c);

#endif
