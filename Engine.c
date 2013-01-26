#include "main.h"
#include "Engine.h"

int Engine_find_way(Map *map) {

	int valid = 1;

	//liste des squares
	RunFIFO *fifo = RunFIFO_create();

	unsigned int row, col;
	unsigned int neighbour;
	Square *currentSquare = NULL;
	Square **neighbourSquares = NULL;

	if (map != NULL && fifo != NULL) {

		row = map->exit[0];
		col = map->exit[1];

		//Récupération de la sortie
		currentSquare = Map_get_square(row, col, map);

		//Empilage de la sortie
		RunFIFO_push(currentSquare, fifo);

		while (!RunFIFO_empty(fifo)) {

			//Récupération de la première case de la file
			currentSquare = RunFIFO_pop(fifo);

			//Récupération des voisins de la case courante
			neighbourSquares = Square_get_neighbours(currentSquare, map);

			if (neighbourSquares != NULL) {
				
				for (neighbour = 0; neighbour < 4 && neighbourSquares[neighbour] != NULL; neighbour++) {
					
					if (Square_set_weight(currentSquare, neighbourSquares[neighbour], map)) {
						//Si le poids du voisin est défini on empile le voisin
						RunFIFO_push(neighbourSquares[neighbour], fifo);

					}
				}

				free(neighbourSquares);
				neighbourSquares = NULL;
			} else {

				valid = 0;
			}
		}
	} else {

		valid = 0;
	}

	RunFIFO_free(fifo);
	fifo = NULL;

	return valid;
}

void Engine_reset_way(Map *map) {

	unsigned int row, col;
	Square *s = NULL;

	for (row = 0; row < map->height; row++) {
		for (col = 0; col < map->width; col++) {

			s = Map_get_square(row, col, map);
			if (s->type != EXIT) {

				s->weight = INFINI;
			} else {

				s->weight = 0;
			}
		}
	}
}

int Engine_round(unsigned int dropLemmingsBuffer, Map *map, Player *p) {

	unsigned int row, col;
	unsigned int enter;
	Square *currentSquare = NULL;
	
	//Pour chaque entrée : si fréquence ok, sortie d'un lemming
	for (enter = 0; enter < map->nbEnter && map != NULL; enter++) {

		if (dropLemmingsBuffer % map->fLemmings == 0) {

			if (map->lemmingsOut < map->nLemmings) {

				Engine_drop_lemming(enter, map);
			}
		}
	}

	for (row = 0; row < map->height; row++) {
		for (col = 0; col < map->width; col++) {

			currentSquare = Map_get_square(row, col, map);
			if (currentSquare->lemming != NULL && currentSquare->move) {
				//Si lemming présent sur le Square
				if (!Engine_life_lemming(currentSquare, map)) {

					Engine_kill_lemming(currentSquare, map);
				}

				if (currentSquare->type == EXIT) {

					Engine_save_lemming(currentSquare, map, p);
				} else if (currentSquare->type == MUD && currentSquare->wait < WAIT_MUD) {

					currentSquare->wait++;
				} else {

					if (currentSquare->type == BOMB ||
						currentSquare->type == BRIDGE ||
						currentSquare->type == CROUS_TICKET ||
						currentSquare->type == STOP) {
						//Récupération de l'item sur la case
						Player_add_item(currentSquare->type, p);
						currentSquare->type = GROUND;
					}

					Engine_move_lemming(currentSquare, map);
					currentSquare->wait = 0;
				}
			} else {

				currentSquare->move = 1;
			}
		}
	}

	return 1;
}

int Engine_drop_lemming(unsigned int enter, Map *map) {

	Lemming *l = Lemming_create();
	Square *s = NULL;

	if (map != NULL && l != NULL) {

		s = Map_get_square(map->enters[enter][0], map->enters[enter][1], map);

		if (s != NULL && s->lemming == NULL) {

			s->lemming = l;
			map->lemmingsOut++;
			return 1;
		}
	}

	return 0;
}

int Engine_save_lemming(Square *s, Map *map, Player *p) {

	if (map != NULL && s != NULL && s->lemming != NULL) {

		p->points += s->lemming->life;

		map->lemmingsSaved++;

		Lemming_free(s->lemming);
		s->lemming = NULL;
		return 1;
	}

	return 0;
}

int Engine_kill_lemming(Square *s, Map *map) {

	if (map != NULL && s != NULL) {

		map->lemmingsDead++;

		Lemming_free(s->lemming);
		s->lemming = NULL;
		return 1;
	}

	return 0;
}

int Engine_move_lemming(Square *s, Map *map) {

	Square *next = NULL;

	if (map != NULL && s != NULL && s->move) {

		next = Square_find_next(s, map);

		if (next != NULL && next->lemming == NULL) {

			next->lemming = s->lemming;
			s->lemming = NULL;
			if (next->row > s->row || next->col > s->col) {
				//Si le square suivant est après dans le parcours de la map
				//Il ne devra pas se déplacer car il vient de se déplacer
				next->move = 0;
			}

			return 1;
		}
	}

	return 0;
}

int Engine_life_lemming(Square *s, Map *map) {

	if (s != NULL && map != NULL) {

		switch (s->type) {

			case CROUS:

				s->lemming->life += (LIFE_MAX - s->lemming->life) / 2;
				break;

			case WATER:

				s->lemming->humid += 1;
				if (s->lemming->life >= 2) {

					s->lemming->life -= 2;
				} else {

					s->lemming->life = 0;
				}
				break;

			case DARK_WATER:

				s->lemming->humid += 2;

				if (s->lemming->life >= 20) {

					s->lemming->life -= 20;
				} else {

					s->lemming->life = 0;
				}
				break;

			case FIRE:

				if (s->lemming->humid == 0) {

					if (s->lemming->life >= 100) {

						s->lemming->life -= 100;
					} else {

						s->lemming->life = 0;
					}
				} else {

					s->lemming->life -= 1;
					s->lemming->humid -= 1;
				}
				break;

			default:

				s->lemming->life -= 1;
				break;
		}

		if (s->lemming->life > 0) {

			return 1;
		}
	}

	return 0;
}

int Engine_place_item(unsigned int type, unsigned int row, unsigned int col, Map *map, Player *p) {

	Square *s = NULL;

	if (map != NULL && row < map->height && col < map->width) {

		s = Map_get_square(row, col, map);

		if (s != NULL) {
			
			//Pour chaque type si suppression on définit le nouveau type 
			//et éventuellement recherche d'un chemin
			switch(type) {
				case BOMB:
					if (s->type == WALL) {

						if (Player_delete_item(type, p)) {
							
							s->type = GROUND;
							Engine_reset_way(map);
							Engine_find_way(map);
						}
					}
					break;
				case BRIDGE:
					if (s->type == WATER || s->type == DARK_WATER) {
						if (Player_delete_item(type, p)) {

							s->type = GROUND;
						}
					}
					break;
				case CROUS_TICKET:
					if (s->type == GROUND) {
						if (Player_delete_item(type, p)) {

							s->type = CROUS;
						}
					}
					break;
				case STOP:
					if (s->type == GROUND || s->type == CROUS) {

					if (Player_delete_item(type, p)) {
							
							s->type = WALL;
							Engine_reset_way(map);
							Engine_find_way(map);
						}
					}
					break;
			}
		}
	}
	return 1;
}