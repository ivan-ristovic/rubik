/*
	This file contains functions and variables that handle working with matrices.
*/

#ifndef _H_MATRICES_H_
#define _H_MATRICES_H_

#include <GL/glut.h>
#include "indicators.h"


/* Matrix size in OpenGL, since it is one dimensional array */
#define MATRIX_SIZE 	16
#define MATRIX_SIZE_N 	 4

/* Number of unit cubes */
#define UNIT_CUBE_NUM	27

/* Number of unit cubes in one layer */
#define UNITS_IN_LAYER	 9

/* These are sin and cos values of our angle step, which is 5 degrees
   The rotations are performed 5 degrees at a time */
#define SINP5 0.087155f
#define SINN5 -SINP5
#define COSP5 0.996194f
#define COSN5 COSP5


/* rotate_matrix array stores composition of all layer rotations for all unit cubes */
extern GLfloat rotate_matrix[UNIT_CUBE_NUM][MATRIX_SIZE];

/* ID matrix */
extern GLfloat ID_MATRIX[MATRIX_SIZE];

/* These matrices are 5 degree rotation matrices around certain axis */
extern GLfloat Y_POS_ROT_MATRIX[MATRIX_SIZE];
extern GLfloat Y_NEG_ROT_MATRIX[MATRIX_SIZE];
extern GLfloat Z_POS_ROT_MATRIX[MATRIX_SIZE];
extern GLfloat Z_NEG_ROT_MATRIX[MATRIX_SIZE];

/* These matrices are 90 degree rotation matrices around certain axis */
extern GLfloat Y_POS_ROT_MATRIX_FULL[MATRIX_SIZE];
extern GLfloat Y_NEG_ROT_MATRIX_FULL[MATRIX_SIZE];
extern GLfloat Z_POS_ROT_MATRIX_FULL[MATRIX_SIZE];
extern GLfloat Z_NEG_ROT_MATRIX_FULL[MATRIX_SIZE];

/* This array will keep the position indexes of all unit cubes.
   For example, when performing a rotation, a cube that was on position 0
   will transfer to position 2, so when we perform next rotation that involves
   cube on position 2, we will apply rotation on the correct cube */
extern int pos[UNIT_CUBE_NUM];


/* Puts identity matrix into matrix pointed to by 'mat' */
void load_id_matrix(GLfloat mat[]);

/* Multiplies 'mat1' and 'mat2' and places result in 'result' */
void multiply_matrices(const GLfloat mat1[], const GLfloat mat2[], GLfloat result[]);

/* Updates pos array. This function is called after each rotation to update the
   positions of unit cubes */
void update_pos_array(int rotation_id);

/* Handles corresponding matrix multiplication cases with 5 degree rotation matrices*/
void multiply_unit_matrices(int move_id);

/* Handles corresponding matrix multiplication cases with 90 degree rotation matrices */
void multiply_unit_matrices_full(int move_id);


#endif
