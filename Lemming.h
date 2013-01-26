#ifndef __LEMMING_H__
#define __LEMMING_H__

#define LIFE_MAX 50

typedef struct lemming {
	unsigned int life;
	unsigned int humid;
} Lemming;

Lemming *Lemming_alloc();
Lemming *Lemming_create();
void Lemming_free(Lemming *l);

void Lemming_printf(Lemming *l);

#endif
