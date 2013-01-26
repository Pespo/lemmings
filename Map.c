#include "main.h"
#include "Map.h"

int Map_set_data(Map *map, ImageRGB *im) {

	unsigned int row, col;
	unsigned int nbExit = 0;
	Color *color = NULL;
	Square *square = NULL;

	if (im->data != NULL && map != NULL) {
		
		for (row = 0; row < im->height; row++) {
			for (col = 0; col < im->width; col++) {
				
				color = ImageRGB_get_color(im, row, col);

				if (color != NULL) {
					
					//Cas pécifiques : ENTER EXIT
					if (color->g == WALL ||
						color->g == WATER ||
						color->g == DARK_WATER ||
						color->g == FIRE ||
						color->g == CROUS ||
						color->g == MUD ||
						color->g == BOMB ||
						color->g == STOP ||
						color->g == BRIDGE ||
						color->g == CROUS_TICKET) {

						square = Square_create(row, col, color->g, INFINI);
						Map_set_square(square, map);
					} else if (color->g == ENTER) {

						//Cas pécifique : ENTER 
						square = Square_create(row, col, color->g, INFINI);
						Map_set_square(square, map);

						Map_add_enter(row, col, map);
						
						Map_set_nLemmings(color->r, map);
						Map_set_fLemmings(color->b, map);
					} else if (color->g == EXIT && nbExit == 0) {

						//Cas pécifique : EXIT 
						nbExit++;

						square = Square_create(row, col, EXIT, 0);
						Map_set_square(square, map);

						Map_set_exit(row, col, map);
					} else {

						square = Square_create(row, col, GROUND, INFINI);
						Map_set_square(square, map);
					}
				} else {

					square = Square_create(row, col, GROUND, INFINI);
					Map_set_square(square, map);
				}

				Color_free(color);
				color = NULL;
			}
		}
	}

	//Il doit y avoir au moins une entrée
	if (map->nbEnter < 1) {

		return 0;
	}
	
	return 1;
}

Square *Map_get_square(unsigned int row, unsigned int col, Map *map) {

	Square *s = NULL;

	if (row < map->height && col < map->width) {

		s = map->sRow[row][col];
	}

	return s;
}

int Map_set_square(Square *s, Map *map) {

	if (s->row < map->height && s->col < map->width) {

		map->sRow[s->row][s->col] = s;

		return 1;
	}

	return 0;
}

int Map_add_enter(unsigned int row, unsigned int col, Map *map) {

	if (map != NULL) {
		
		if (map->nbEnter == 0) {

			//Première entrée
			map->enters = (unsigned int**) malloc(sizeof(unsigned int*));
		} else {

			map->enters = (unsigned int**) realloc(map->enters, sizeof(unsigned int*) * (map->nbEnter + 1));
		}
		
		map->enters[map->nbEnter] = (unsigned int*) malloc(sizeof(unsigned int));
		
		map->enters[map->nbEnter][0] = row;
		map->enters[map->nbEnter][1] = col;
		
		map->nbEnter++;

		return 1;
	}

	return 0;
}

int Map_set_exit(unsigned int row, unsigned int col, Map *map) {

	if (map != NULL) {

		map->exit[0] = row;
		map->exit[1] = col;

		return 1;
	}

	return 0;
}

void Map_set_fLemmings(unsigned int fLemmings, Map *map) {

	if (fLemmings < 1 || fLemmings > 254)
		
		//Valeur moyenne
		fLemmings = 126;

	map->fLemmings = fLemmings;
}

void Map_set_nLemmings(unsigned int nLemmings, Map *map) {

	if (nLemmings < 1 || nLemmings > 254)

		//Valeur moyenne
		nLemmings = 126 * map->nbEnter;

	map->nLemmings = nLemmings * map->nbEnter;
}

Map *Map_load(char *filePath) {
	
	ImageRGB *im = ImageRGB_load(filePath);
	Map *map = Map_create(im->width, im->height);
	
	if (im != NULL && map != NULL) {
		
		//Définition des pixels de la map
		Map_set_data(map, im);
		
		ImageRGB_free(im);
		im = NULL;
	}
	
	return map;
}

Map *Map_create(unsigned int width, unsigned int height) {
	
	Map *map = Map_alloc(width, height);
	
	if (map != NULL) {
		
		map->width = width;
		map->height = height;
		map->fLemmings = 126;
		map->nLemmings = 126;
		map->lemmingsOut = 0;
		map->lemmingsDead = 0;
		map->lemmingsSaved = 0;
		map->nbEnter = 0;
		
	}
	return map;
}

Map *Map_alloc(unsigned int width, unsigned int height) {
	
	unsigned int row;
	Map *map = NULL;
	
	//Allocation de la strucutre image
	map = (Map*) malloc(sizeof(Map));
	
	if (map != NULL) {
		
		//Allocation du tableau de données
		map->squares = (Square**) malloc(width * height * sizeof(Square*));
		
		if (map->squares != NULL) {
			
			//Allocation du tableau de pointeurs de début de lignes
			map->sRow = (Square***) malloc(height * sizeof(Square**));
			
			if (map->sRow != NULL) {
				
				for (row = 0; row < height; row++) {
					
					map->sRow[row] = &(map->squares[row * width]);
				}
				
			} else {
				
				Map_free(map);
				map = NULL;
			}
		} else {
			
			Map_free(map);
			map = NULL;
		}
	}
	
	return map;
}

void Map_free(Map *map) {
	
	unsigned int row, col;
	
	//Désallocation des Square
	for (row = 0; row < map->height; row++) {
		for (col = 0; col < map->width; col++) {
			Square_free(map->sRow[row][col]);
		}
	}
	
	//Désallocation des données
	free(map->squares);
	
	//Désallocation des pointeurs de début de ligne
	free(map->sRow);
	
	//Désallocation des entrées
	free(map->enters);
	
	//Désallocation de la structure
	free(map);
}

void Map_printf(Map *map) {

	unsigned int row, col;
	unsigned int enter;
	Square *s = NULL;

	printf("Map at %p : \n", map);
	printf("\t    width : %d\n", map->width);
	printf("\t   height : %d\n", map->height);
	printf("\t squares at %p\n", map->squares);
	printf("\t	  sRow at %p\n", map->sRow);
	printf("\tnLemmings : %d\n", map->nLemmings);
	printf("\tfLemmings : %d\n", map->fLemmings);
	printf("\n");
	printf("--SQUARES type\n");

	for (row = 0; row < map->height; row++) {
		for (col = 0; col < map->width; col++) {
			
			s = Map_get_square(row, col, map);
			printf("%d\t", s->type);
		}
		printf("\n");
	}

	printf("\n");
	printf("--SQUARES weight\n");

	for (row = 0; row < map->height; row++) {
		for (col = 0; col < map->width; col++) {
			s = Map_get_square(row, col, map);
			printf("%d\t", s->weight);
		}
		printf("\n");
	}

	printf("\n");
	printf("--LEMMINGS\n");
	
	for (row = 0; row < map->height; row++) {
		for (col = 0; col < map->width; col++) {
			s = Map_get_square(row, col, map);
			if (s->lemming == NULL) {
				
				printf("_\t");
			} else {
				char c = (((int) s->lemming) % 26) + 65;
				printf("%c\t", c);
			}
		}
		printf("\n");
	}
	
	printf("\n");
	printf("--EXIT\n");

	printf("Exit at %p : \n", map->exit);
	printf("\trow : %d\n", map->exit[0]);
	printf("\tcol : %d\n", map->exit[1]);

	printf("\n");
	printf("--ENTER(s)\n");
	
	printf("Enters at %p : \n", map->enters);

	for (enter = 0; enter < map->nbEnter && map != NULL; enter++) {
		printf("\trow : %d\n", map->enters[enter][0]);
		printf("\tcol : %d\n", map->enters[enter][1]);
	}

	printf("------------------------------------------\n\n");
}
