#ifndef __SQUARE_H__
#define __SQUARE_H__

#define GROUND 0
#define WALL 1
#define WATER 2
#define DARK_WATER 3
#define FIRE 4
#define CROUS 5
#define MUD 6
#define EXIT 7
#define ENTER 8
#define BOMB 9
#define STOP 10
#define BRIDGE 11
#define CROUS_TICKET 12
#define RABBIT 13

#define WAIT_MUD 1

struct map;

typedef struct square {
	unsigned int row;
	unsigned int col;
	unsigned int type;
	unsigned int weight;
	unsigned int wait;
	unsigned int move;
	Lemming *lemming;
} Square;

Square **Square_get_neighbours(Square *s, struct map *map);
int Square_set_weight(Square *ref, Square *s, struct map *map);
Square *Square_find_next(Square *s, struct map *map);

Square *Square_create(unsigned int row, unsigned int col, unsigned int type, unsigned int weight);
void Square_free(Square *s);

void Square_printf(Square *s);

#endif
