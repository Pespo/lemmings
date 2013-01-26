#include "main.h"
#include "Lemming.h"

Lemming *Lemming_alloc() {
	
	Lemming *l = (Lemming*) malloc(sizeof(Lemming));
	
	return l;
}

Lemming *Lemming_create() {
	
	Lemming *l = Lemming_alloc();

	if (l != NULL) {
		l->life = LIFE_MAX;
		l->humid = 0;
	}
	
	return l;
}

void Lemming_free(Lemming *l) {
	
	free(l);
}

void Lemming_printf(Lemming *l) {

	printf("Lemming at %p : \n", l);
	printf("\t life : %d\n", l->life);
	printf("\thumid : %d\n", l->humid);
	printf("------------------------------------------\n\n");
}