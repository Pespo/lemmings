	#include "main.h"

int main(int argc, char **argv) {
	
	printf("%s\n", __FILE__);
	srand(time(NULL));

	texturePaths[GROUND][0] = "ground.pbm";
	texturePaths[GROUND][1] = "stdmask.pbm";
	texturePaths[WALL][0] = "wall.pbm";
	texturePaths[WALL][1] = "stdmask.pbm";
	texturePaths[WATER][0] = "water.pbm";
	texturePaths[WATER][1] = "stdmask.pbm";
	texturePaths[DARK_WATER][0] = "darkwater.pbm";
	texturePaths[DARK_WATER][1] = "stdmask.pbm";
	texturePaths[FIRE][0] = "fire.pbm";
	texturePaths[FIRE][1] = "stdmask.pbm";
	texturePaths[CROUS][0] = "crous.pbm";
	texturePaths[CROUS][1] = "stdmask.pbm";
	texturePaths[MUD][0] = "mud.pbm";
	texturePaths[MUD][1] = "stdmask.pbm";
	texturePaths[EXIT][0] = "exit.pbm";
	texturePaths[EXIT][1] = "stdmask.pbm";
	texturePaths[ENTER][0] = "enter.pbm";
	texturePaths[ENTER][1] = "stdmask.pbm";
	texturePaths[BOMB][0] = "bomb.pbm";
	texturePaths[BOMB][1] = "bombmask.pbm";
	texturePaths[STOP][0] = "stop.pbm";
	texturePaths[STOP][1] = "stopmask.pbm";
	texturePaths[BRIDGE][0] = "bridge.pbm";
	texturePaths[BRIDGE][1] = "bridgemask.pbm";
	texturePaths[CROUS_TICKET][0] = "crous_ticket.pbm";
	texturePaths[CROUS_TICKET][1] = "crous_ticketmask.pbm";
	texturePaths[RABBIT][0] = "rabbit.pbm";
	texturePaths[RABBIT][1] = "rabbitmask.pbm";
	
	dropLemmingsBuffer = 0;
    zoom = 1;
    moveX = 0; moveY = 1;
    clicRow = - 1;
	clicCol = -1;
	pause = 1;
	
	sizeAbsolutePath = strlen(__FILE__);
	absolutePath = (char*) malloc(sizeof(char) * sizeAbsolutePath);
	sizeAbsolutePath += 50;
	sprintf(absolutePath, "%.*s", strrchr(__FILE__, '/') - __FILE__ + 1, &__FILE__[0]);
	
	gMap = init_lemmings(argc, argv);
	
	if (!Engine_find_way(gMap)) {
		
		return 0;
	}
	
    if (gMap->width > gMap->height) {
		
        if (gMap->height < SIZE_MAP_MAX) {
			
            mapSize = gMap->height+1 ;
        } else {
			
            mapSize = SIZE_MAP_MAX;
        }
    } else {
		
        if (gMap->width < SIZE_MAP_MAX) {
         
			mapSize = gMap->width;
        } else {
            
			mapSize = SIZE_MAP_MAX;
        }
    }

	static unsigned int itemsId[NB_ITEMS] = {9, 10, 11, 12};
	gPlayer = Player_create(itemsId);
	
	//Glut initialisations
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(5, 5);
	glutInitWindowSize(SCREEN_SIZE, SCREEN_SIZE);

	//Fenêtre de Map
	winIdMain = glutCreateWindow ("Lemmings");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glMap_load_texture(gMap);
	glutDisplayFunc(mainDisplay);
	glutReshapeFunc(mainReshape);
	glutKeyboardFunc(IHM_keyboard);
	glutMouseFunc(IHM_mouse);
	glutIdleFunc(idle);

	//Fenêtre de menu
	winIdSub = glutCreateSubWindow(winIdMain, 0, 0, SCREEN_SIZE , SCREEN_SIZE / 10);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glMap_load_texture(gMap);
	glutDisplayFunc(subDisplay);
	glutReshapeFunc(subReshape);

	glutMainLoop();

	return 1;
}

void idle() {

	if (!pause && (gMap->lemmingsDead + gMap->lemmingsSaved < gMap->nLemmings)) {

		static int lastUpdate = 0;

		int currentTime = glutGet(GLUT_ELAPSED_TIME);

		if ((currentTime - lastUpdate) >= 500) {

			Engine_round(dropLemmingsBuffer, gMap, gPlayer);
			if (dropLemmingsBuffer == 0 || dropLemmingsBuffer % gMap->fLemmings != 0) {

				dropLemmingsBuffer++;
			} else {

				dropLemmingsBuffer = 1;
			}

			lastUpdate = currentTime;
		}
		glutSetWindow (winIdMain);
		glutPostRedisplay ();
		glutSetWindow (winIdSub);
		glutPostRedisplay ();
	}
}

void mainDisplay() {

    glutSetWindow (winIdMain);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    glPushMatrix();
        glScalef( zoom, zoom, 1);
		glTranslatef( moveX, moveY, 0);
        IHM_draw_map(gMap);
    glPopMatrix();
    glutSwapBuffers ();
}

void subDisplay() {

	glutSetWindow (winIdSub);
	glClearColor (0.8, 0.8, 0.8, 0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
//	glColor4b(0, 255, 0, 255);
	glBegin (GL_LINE_LOOP);
		glVertex2f (0.01, 0.01);
		glVertex2f (0.0, 1.99);
		glVertex2f (15.999, 1.99);
		glVertex2f (15.999, 0.01);
	glEnd ();

	IHM_draw_menu(gPlayer, gMap);

	glutSwapBuffers ();
}

void mainReshape(int w, int h) {

	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	if ( w > h )
		gluOrtho2D(0.0, mapSize *((float) w/h), mapSize , 0.0);
	else
		gluOrtho2D(0.0, mapSize , mapSize *((float) h/w), 0.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	glutSetWindow (winIdSub);
	glutReshapeWindow (w, h / mapSize);
	glutPositionWindow (0, 0);
	glutSetWindow (winIdMain);

}

void subReshape(int w, int h) {
	
	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0, 16, 2, 0);
}

Map *init_lemmings(int argc, char **argv) {

	Map *map = NULL;
	//Deux arguments obligatoires !
	int i;

	//Si un seul argument
	if (argc == 2) {

		//Demande d'aide ?
		if (argv[1][0] != '-' || argv[1][1] != 'h') {

			printf("USAGE : lemmings -m path [-f frequency] [-n number] [-h]\n\n");
			return NULL;
		}

		help();
		return NULL;
	}

	//Si aucun arguments
	if (argc < 2) {

		printf("Vous n'avez pas passé assez d'argument\n\n");
		return NULL;
	}

	//Si nombre impaire d'argument || trop d'arguments
	if ((argc % 2) != 1 || argc > 7) {
		printf("%d, %s, %s, %s, %s",argc, argv[0], argv[1], argv[2], argv[3]);
		printf("Erreur dans l'utilisataion des arguments\n\n");
		return NULL;
	}

	for (i = 1; i < argc; i++) {

		//Argument -m (path de la map)
		if (argv[i][0] == '-' && argv[i][1] == 'm' && argv[i][2] =='\0' ) {

			char *path = (char*) malloc(sizeof(char) * sizeAbsolutePath);
			strncpy(path, absolutePath, sizeAbsolutePath);
			strncat(path, "maps/", sizeAbsolutePath);
			strncat(path, argv[i + 1], sizeAbsolutePath);
			
			map = Map_load(path);
			if (map == NULL) {

				printf("Error with map file\n");
				return NULL;
			}
			
			free(path);
		}

		//Argument -f (fréquence de chute des lemmings)
		if (argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] =='\0') {

			//La fréquence doit êre comprise en 1 et 254
			if (atoi(argv[i + 1]) < 1 || atoi(argv[i + 1]) > 254) {

				printf("The choosen frequency is wrong. Must be between 1 and 254\n");
				return NULL;
			}

			Map_set_fLemmings(atoi(argv[i + 1]), map);
		}

		//Argument -n (nombre de lemmings)
		if (argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] =='\0') {

			//Le nombre de lemmings doit êre compris en 1 et 254
			if (atoi(argv[i + 1]) < 1 || atoi(argv[i + 1]) > 254) {

				printf("The choosen lemming's number is wrong. Must be between 1 and 254\n");
				return NULL;
			}

			Map_set_nLemmings(atoi(argv[i + 1]), map);
		}

		//Test d'arguments inexistants
		if ((i % 2) == 1){

			if (argv[i][0] != '-' || (argv[i][1] != 'm' && argv[i][1] != 'f' && argv[i][1] != 'n') || argv[i][2] !='\0') {

				printf("Mauvaise combinaison d'arguments\n");
				printf("USAGE : lemmings -m path [-f frequency] [-n number] [-h]\n\n");
				return NULL;
			}
		}
	}
	return map;
}

void help() {
	
	printf("USAGE\n");
	printf("\tlemmings -m path [-n number] [-f frequency]\n\n");

	printf("DETAILS\n");
	printf("\t-m path : path for the map (file must be a P6 ppm image)\n\n");

	printf("\t-n number : set number of lemmings (1 <= n <= 254)\n");
	printf("\t-f frequency : set frequency of the lemmings (1 <= f <= 254)\n\n\n");

	printf("------------\n");
	printf("--lemmings--\n\n");

	printf("Développé par Tom GAY et Guillaume ALBESPY\n");
}
