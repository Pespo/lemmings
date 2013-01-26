#include "main.h"
#include "Color.h"

int Color_compare(Color *c1, Color *c2) {
	
	if (c1->r != c2->r || c1->g != c2->g || c1->b != c2->b) {
		return 0;
	}
	
	return 1;
}

Color *Color_create(unsigned char r, unsigned char g, unsigned char b) {
	
	Color *c = (Color*) malloc(sizeof(Color));
	
	if (c != NULL) {
		
		c->r = r;
		c->g = g;
		c->b = b;
		
		//Récupération de la transparence
		if (c->g == 255 && c->b == 255) {
			
			c->a = c->r;
		} else {
			
			c->a = 255;
		}
	}
	
	return c;
}

void Color_free(Color *c) {
	
	free(c);
}

void Color_printf(Color *c) {
	printf("Color at %p : \n", c);
	printf("\t  red : %d\n", c->r);
	printf("\tgreen : %d\n", c->g);
	printf("\t blue : %d\n", c->b);
	printf("\t alpha : %d\n", c->a);
	printf("------------------------------------------\n\n");
}