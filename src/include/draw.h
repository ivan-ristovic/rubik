/*
	This file contains functions that draw elements (ex. cube piece).
*/

#ifndef _H_DRAW_H_
#define _H_DRAW_H_

#include <GL/glut.h>
#include "matrices.h"
#include "textures.h"


/* Unit cube half-size */
#define UNIT_HALFSIZE 0.5


/* Draws unit cube with center at (x, y, z) */
void draw_unit_cube(float x, float y, float z);

/* Draws Rubik's cube made of 27 unit cubes. Center at (x, y, z) */
void draw_rubik_cube(float x, float y, float z);

/* Draws background canvas */
void draw_background(void);


#endif
