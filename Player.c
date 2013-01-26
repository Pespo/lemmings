#include "main.h"
#include "Player.h"

int Player_add_item(unsigned int type, Player *p) {
	
	unsigned int item;
	
	for (item = 0; item < NB_ITEMS && p != NULL; item++) {
		
		if (type == p->items[item][0]) {
			
			p->items[item][1]++;
			return 1;
		}
	}
	
	return 0;
}

int Player_delete_item(unsigned int type, Player *p) {
	
	unsigned int item;
	
	for (item = 0; item < NB_ITEMS && p != NULL; item++) {
		
		if (type == p->items[item][0] && p->items[item][1] > 0) {
			
			p->items[item][1]--;
			return 1;
		}
	}
	
	return 0;
}

Player *Player_create(unsigned int *itemsId) {
	
	Player *p = Player_alloc();
	unsigned int item;
	
	if (p != NULL) {
		
		p->points = 0;
		
		for (item = 0; item < NB_ITEMS; item++) {
				
			p->items[item][0] = itemsId[item];
			p->items[item][1] = 0;
		}
	}
	
	return p;
}

Player *Player_alloc() {
	
	Player *p = (Player*) malloc(sizeof(Player));
	
	return p;
}

void Player_free(Player *p) {
	
	free(p);
}

void Player_printf(Player *p) {
	
	unsigned int item;
	
	printf("Player at %p : \n", p);
	printf("\tpoints : %d\n", p->points);

	for (item = 0; item < NB_ITEMS; item++) {
		
		printf("\t  item at %p :\n", p->items[item]);
		printf("\t\t    type : %d\n", p->items[item][0]);
		printf("\t\t  number : %d\n", p->items[item][1]);
	}
	printf("------------------------------------------\n\n");
}