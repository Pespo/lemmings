#ifndef __ENGINE_H__
#define __ENGINE_H__

#define INFINI UINT_MAX

int Engine_find_way(Map *map);
void Engine_reset_way(Map *map);

int Engine_round(unsigned int dropLemmingsBuffer, Map *map, Player *p);

int Engine_drop_lemming(unsigned int enter, Map *map);
int Engine_save_lemming(Square *s, Map *map,  Player *p);
int Engine_kill_lemming(Square *s, Map *map);
int Engine_move_lemming(Square *s, Map *map);
int Engine_life_lemming(Square *s, Map *map);

int Engine_place_item(unsigned int type, unsigned int row, unsigned int col, Map *map, Player *p);

#endif
