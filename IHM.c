#include "main.h"
#include "IHM.h"

void IHM_keyboard(unsigned char key,int x,int y) {

	switch (key) {
			
		case 'm' :
		case 'M' :
		case 1 :// selectionne stop
			
			Engine_place_item(STOP, clicRow, clicCol, gMap, gPlayer);
			break;

		case 'b' :
		case 'B' :
		case  2 :// selectionne bomb
			
			Engine_place_item(BOMB, clicRow, clicCol, gMap, gPlayer);
			break;

		case 'c' :
		case 'C' :
		case 3 : // selectionne crous
		
			Engine_place_item(CROUS_TICKET, clicRow, clicCol, gMap, gPlayer);
			break;

		case 'p' :
		case 'P' :
		case 4 : // selectionne pont
			
			Engine_place_item(BRIDGE, clicRow, clicCol, gMap, gPlayer);
			break;
			
		case 27: // quitter
			
			Map_free(gMap);
			Player_free(gPlayer);
			free(absolutePath);
			exit(0);
			break;

		case 's' :
		case 'S' ://Déplacement bas
			
			if(mapSize >= (gMap->height + moveY));
			else moveY -= zoom;
			break;

		case 'z' :
		case 'Z' ://Déplacement haut
			
			if(mapSize >= (gMap->height - (moveY + gMap->height - mapSize)+1));
			else moveY += zoom;
			break;

		case 'd' :
		case 'D' ://Déplacement droite
			
			if(mapSize >= (gMap->width + moveX));
			else moveX -= zoom;
			break;

		case 'q' :
		case 'Q' ://Déplacement gauche
			
			if(mapSize >= (gMap->width - (2*moveX + gMap->width - mapSize)));
			else moveX += zoom;
			break;

		case 13	:
		case 32	: //Pause
			
			pause = pause ? 0 : 1;
			break;

		default : //Annulation du click utilisateur
			
			clicRow = - 1;
			clicCol = -1;
			break;
	}
	glutPostRedisplay();
}

void IHM_mouse(int button, int state,int x,int y){

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

		clicCol =(int) x / (SCREEN_SIZE / mapSize) - moveX ;
		clicRow =(int) y / (SCREEN_SIZE / mapSize) - moveY ;
	}

}

void IHM_draw_map(Map *map) {
	
	Square *square;
	unsigned int i, j;
    
	for (i = 0; i < map->height; i++) {
		for (j = 0 ; j < map->width ; j++) {
	
			square = Map_get_square(i, j, map);
			glSquare_draw(square, textureId);
		}
	}
}

void IHM_draw_menu(Player *p, Map *map) {
	
	char text[10];
    Square *square = Square_create(0, 0, 0, 0);
	unsigned int i,j;
    
	for (i = 0; i < NB_ITEMS; i+=2) {
        for (j = 0; j < 2; j++){
    
			square->col = j*2;
            square->row = i/2;
            square->type = p->items[i+j][0];
			
			glSquare_draw_menu(square, textureId);
			
            square->col = j*2+1 ;
			
			sprintf(text, "x %i", p->items[i+j][1]);
			glSquare_write(square, text);
        }
	}
	
    //Reste a sortir	
    square->col += 1 ;
    square->type = 13;
	glSquare_draw_menu(square, textureId);
	
	square->row-- ;
	sprintf(text, "    LEFT");
	glSquare_write(square, text);
	square->row++;
	
    square->col += 1 ;
	sprintf(text, "x %i", (map->nLemmings - map->lemmingsOut));
    glSquare_write(square, text);
	
    //Sauvés
    square->col += 1 ;
    square->type = 13;
	glSquare_draw_menu(square, textureId);
	
	square->row-- ;
	sprintf(text, " SAVED");
	glSquare_write(square, text);
	square->row++;
	
    square->col += 1 ;
	sprintf(text, "x %i", (map->lemmingsSaved));
    glSquare_write(square, text);
	
	//Mort
    square->col += 1 ;
    square->type = 13;
	glSquare_draw_menu(square, textureId);
	
	square->row-- ;
	sprintf(text, "  DEAD");
	glSquare_write(square, text);
	square->row++;
	
    square->col += 1 ;
	sprintf(text, "x %i", (map->lemmingsDead));
    glSquare_write(square, text);
	
	//Points
	square->col += 3;
	sprintf(text, "%i Pts", p->points);
    glSquare_write(square, text);
	Square_free(square);
	square = NULL;
}