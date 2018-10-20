/*
	This file contains function that are initializing certain elements
	(ex. rotation matrices, lighting, textures).
*/

#ifndef _H_INIT_H_
#define _H_INIT_H_

#include <GL/glut.h>
#include "callbacks.h"
#include "indicators.h"
#include "matrices.h"
#include "textures.h"


#define min(a, b) (a < b ? a : b)

/* Initial window size */
#define INIT_WINDOW_SIZE	500

/* Minimum window size (reshape will not shrink window to size less than this) */
#define MIN_WINDOW_SIZE 	300


/* Initializes all handler functions */
void initialize_callbacks(void);

/* Initializes glut */
void initialize_glut(int *argc, char **argv);

/* Creates a light and initializes it's properties */
void initialize_light(void);

/* Initializes rotation matrices and position array */
void initialize_matrices(void);

/* Initializes background texture */
void initialize_textures(void);

/* To be called at program exit */
void free_resources(void);


#endif
