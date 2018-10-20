/*
	This file contains functions that randomize the cube
*/

#ifndef _H_RAND_H_
#define _H_RAND_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include "indicators.h"
#include "matrices.h"


/* Number of different moves */
#define MOVE_NUM 16

/* Ammount of steps during randomization process */
#define RANDOMIZATION_STEPS_NUM 1000


/* Updates rotation matrices for unit cube pieces to match a randomly
   generated move sequence */
void randomize_cube(int num_iter);

/* Performs a random move */
void perform_random_move(unsigned seed);


#endif
