#ifndef __PLAYER_H__
#define __PLAYER_H__

#define NB_ITEMS 4

typedef struct player {
	unsigned int points;
	unsigned int items[NB_ITEMS][2];
} Player;

int Player_add_item(unsigned int type, Player *p);
int Player_delete_item(unsigned int type, Player *p);

Player *Player_create(unsigned int *itemsId);
Player *Player_alloc();
void Player_free();

void Player_printf(Player *p);
	
#endif
