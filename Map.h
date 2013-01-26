#ifndef __MAP_H__
#define __MAP_H__

typedef struct map {
	unsigned int width;
	unsigned int height;
	Square ***sRow;
	Square **squares;
	unsigned int fLemmings;
	unsigned int nLemmings;
	unsigned int **enters;
	unsigned int exit[2];
	unsigned int lemmingsOut;
	unsigned int lemmingsDead;
	unsigned int lemmingsSaved;
	unsigned int nbEnter;
} Map;

int Map_set_data(Map *map, ImageRGB *im);

Square *Map_get_square(unsigned int row, unsigned int col, Map *map);
int Map_set_square(Square *s, Map *map);

int Map_add_enter(unsigned int row, unsigned int col, Map *map);
int Map_set_exit(unsigned int row, unsigned int col, Map *map);

void Map_set_fLemmings(unsigned int fLemmings, Map *map);
void Map_set_nLemmings(unsigned int nLemmings, Map *map);

Map *Map_load(char *filePath);
Map *Map_create(unsigned int width, unsigned int height);
Map *Map_alloc(unsigned int width, unsigned int height);
void Map_free(Map *map);

void Map_printf(Map *map);

#endif
