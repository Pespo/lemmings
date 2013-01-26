#ifndef __IHM_H__
#define __IHM_H__

#define MENU_SIZE 2
#define SIZE_MAP_MAX 30
#define SCREEN_SIZE 600
#ifndef GLUT_BITMAP_HELVETICA_12
	#define GLUT_BITMAP_HELVETICA_12 ((void*)2)
#endif

void IHM_keyboard(unsigned char key,int x,int y);
void IHM_mouse(int button, int state,int x,int y);

void IHM_draw_map(Map *map);
void IHM_draw_menu(Player *p, Map *map);

#endif
