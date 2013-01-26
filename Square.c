	#include "main.h"
#include "Square.h"

Square **Square_get_neighbours(Square *s, Map *map) {

	int row, col;
	int neighbourRow, neighbourCol;
	Square *neighbour = NULL;
	Square **neighbours = NULL;
	int nbNeig = 0;

	neighbours = (Square**) malloc(sizeof(Square*) * 4);
	neighbours[0] = neighbours[1] = neighbours[2] = neighbours[3] = NULL;

	if (s != NULL && map != NULL && neighbours != NULL) {

		row = s->row;
		col = s->col;

		//Voisins haut et bas
		for (neighbourRow = row - 1; neighbourRow <= row + 1; neighbourRow += 2) {
			//Si le voisin est dans la map
			if (neighbourRow < map->height) {
				neighbour = Map_get_square(neighbourRow, col, map);

				if (neighbour != NULL && neighbour->type != WALL) {

					neighbours[nbNeig] = neighbour;
					nbNeig++;
				}
			}
		}

		//Voisins gauche et droite
		for (neighbourCol = col - 1; neighbourCol <= col + 1; neighbourCol += 2) {

			if (neighbourCol < map->width) {
				neighbour = Map_get_square(row, neighbourCol, map);

				if (neighbour != NULL && neighbour->type != WALL) {

					neighbours[nbNeig] = neighbour;
					nbNeig++;
				}
			}
		}
	}

	return neighbours;
}

int Square_set_weight(Square *ref, Square *s, Map *map) {

	if (s != NULL && ref != NULL && map != NULL) {

		if (s->type != WALL) {

			//Si c'est de la boue le poids est 2 sinon 1
			if (ref->weight + 1 < s->weight && s->type != MUD) {

				s->weight = ref->weight + 1;
			} else if (ref->weight + 2 < s->weight && s->type == MUD) {

				s->weight = ref->weight + 2;
			} else {

				return 0;
			}

			return 1;
		}
	}

	return 0;
}

Square *Square_find_next(Square *s, Map *map) {

	unsigned int neighbour;
	unsigned int possibleNeighboursCpt = 0;
	unsigned int possibleNeighboursId[4];
	unsigned int minWeight;

	Square **neighbours = NULL;

	if (s != NULL && map != NULL) {

		minWeight = s->weight;
		neighbours = Square_get_neighbours(s, map);

		//Récupération du plus petit poids des voisins
		for (neighbour = 0; neighbour < 4 && neighbours[neighbour] != NULL; neighbour++) {

			if (neighbours[neighbour]->weight <= minWeight) {
				
				minWeight = neighbours[neighbour]->weight;
			}
		}
		
		//récupération de tous les voisins au plus petit poids
		for (neighbour = 0; neighbour < 4 && neighbours[neighbour] != NULL; neighbour++) {

			if (neighbours[neighbour]->weight <= minWeight) {

				possibleNeighboursId[possibleNeighboursCpt] = neighbour;
				possibleNeighboursCpt++;
			}
		}
		
		if (possibleNeighboursCpt > 0) {

			unsigned int rN = (unsigned int) rand() % possibleNeighboursCpt;
			return neighbours[possibleNeighboursId[rN]];
		}
	}

	return NULL;
}

Square *Square_create(unsigned int row, unsigned int col, unsigned int type, unsigned int weight) {
	
	Square *s = (Square*) malloc(sizeof(Square));
	
	if (s != NULL) {
		
		s->row = row;
		s->col = col;
		s->type = type;
		s->weight = weight;
		s->move = 1;
        s->lemming = NULL;
	}
	
	return s;
}

void Square_free(Square *s) {
	
	//Désallocation des données
	free(s);
	
	Lemming_free(s->lemming);
	s->lemming = NULL;
	
}

void Square_printf(Square *s) {
	printf("Square at %p : \n", s);
	printf("\t   row : %d\n", s->row);
	printf("\t   col : %d\n", s->col);
	printf("\t  type : %d\n", s->type);
	printf("\tweight : %d\n", s->weight);
	printf("------------------------------------------\n\n");
}
