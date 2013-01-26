#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/glut.h>
#endif
#ifdef __linux__
	#include <GL/glut.h>
	#include <GL/gl.h>
#endif
#ifdef WIN32
    #include <windows.h>
	#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "Lemming.h"
#include "Square.h"
#include "Color.h"
#include "Player.h"
#include "ImageRGB.h"
#include "ImageRGBA.h"
#include "Map.h"
#include "RunFIFO.h"
#include "Engine.h"
#include "glMap.h"
#include "glSquare.h"
#include "IHM.h"

//Init functions
Map *init_lemmings(int argc, char **argv);
void help();

//Glut functions
void mainDisplay(void);
void mainReshape(int w, int h);
void subDisplay(void);
void subReshape(int w, int h);
void idle();

//Globals
char *absolutePath;
int sizeAbsolutePath;
int mapSize;
int dropLemmingsBuffer;
float ratioWindow;
float zoom;
float moveX;
float moveY;
Map *gMap;
Player *gPlayer;
GLuint textureId[NB_TEXTURES];
char *texturePaths[NB_TEXTURES][2];
int winIdMain;
int winIdSub;
int clicCol;
int clicRow;
int pause;

#endif
