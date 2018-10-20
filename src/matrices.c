#include "include/matrices.h"


/* ID matrix */

GLfloat ID_MATRIX[MATRIX_SIZE] = {
	    1,     0,     0,     0,
 	    0,     1,     0,     0,
	    0,     0,     1,     0,
	    0,     0,     0,     1
};

/* 5 degree rotation matrices */

GLfloat Y_POS_ROT_MATRIX[MATRIX_SIZE] = {
	COSP5,     0, SINP5,     0,
 	    0,     1,     0,     0,
	SINN5,     0, COSP5,     0,
	    0,     0,     0,     1
};

GLfloat Y_NEG_ROT_MATRIX[MATRIX_SIZE] = {
	COSP5,     0, SINN5,     0,
	    0,     1,     0,     0,
	SINP5,     0, COSP5,     0,
	    0,     0,     0,     1
};

GLfloat Z_POS_ROT_MATRIX[MATRIX_SIZE] = {
	COSP5, SINN5,     0,     0,
	SINP5, COSP5,     0,     0,
	    0,     0,     1,     0,
	    0,     0,     0,     1
};

GLfloat Z_NEG_ROT_MATRIX[MATRIX_SIZE] = {
	COSP5, SINP5,     0,     0,
	SINN5, COSP5,     0,     0,
	    0,     0,     1,     0,
	    0,     0,     0,     1
};

/* 90 degree rotation matrices */

GLfloat Y_POS_ROT_MATRIX_FULL[MATRIX_SIZE] = {
	    0,     0,     1,     0,
 	    0,     1,     0,     0,
	   -1,     0,     0,     0,
	    0,     0,     0,     1
};

GLfloat Y_NEG_ROT_MATRIX_FULL[MATRIX_SIZE] = {
	    0,     0,    -1,     0,
	    0,     1,     0,     0,
	    1,     0,     0,     0,
	    0,     0,     0,     1
};

GLfloat Z_POS_ROT_MATRIX_FULL[MATRIX_SIZE] = {
	    0,    -1,     0,     0,
	    1,     0,     0,     0,
	    0,     0,     1,     0,
	    0,     0,     0,     1
};

GLfloat Z_NEG_ROT_MATRIX_FULL[MATRIX_SIZE] = {
	    0,     1,     0,     0,
	   -1,     0,     0,     0,
	    0,     0,     1,     0,
	    0,     0,     0,     1
};


/* Unit cube matrices array */
GLfloat rotate_matrix[UNIT_CUBE_NUM][MATRIX_SIZE];

/* Unit cube position array */
int pos[UNIT_CUBE_NUM];


void load_id_matrix(GLfloat mat[])
{
	int i;
	for (i = 0; i < MATRIX_SIZE; i++)
		mat[i] = ID_MATRIX[i];
}

void multiply_matrices(const GLfloat mat1[], const GLfloat mat2[], GLfloat result[])
{
	/* Current result is zero matrix */
	GLfloat tmp_result[MATRIX_SIZE] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	/* Multiplying matrices */
	int i, j, k;
	for (i = 0; i < MATRIX_SIZE_N; i++)
		for (j = 0; j < MATRIX_SIZE_N; j++)
			for (k = 0; k < MATRIX_SIZE_N; k++)
				tmp_result[MATRIX_SIZE_N*i+j] += mat2[MATRIX_SIZE_N*i+k] * mat1[MATRIX_SIZE_N*k+j];

	/* Copying calculated result into 'result' */
	for (i = 0; i < MATRIX_SIZE; i++)
		result[i] = tmp_result[i];
}

void update_pos_array(int rotation_id)
{
	/* We need to save the current array state, before replacing it's elements */
	int copy[UNIT_CUBE_NUM], i;
	for (i = 0; i < UNIT_CUBE_NUM; i++) {
		copy[i] = pos[i];
	}

	/* Based on rotation ID, we are updating position array */
	switch (rotation_id) {

		case ID_YNEG:
			update_pos_array(ID_LAYERYNEG_0);
			update_pos_array(ID_LAYERYNEG_1);
			update_pos_array(ID_LAYERYNEG_2);
			break;
		case ID_YPOS:
			update_pos_array(ID_LAYERYPOS_0);
			update_pos_array(ID_LAYERYPOS_1);
			update_pos_array(ID_LAYERYPOS_2);
			break;
		case ID_ZNEG:
			update_pos_array(ID_LAYERZNEG_0);
			update_pos_array(ID_LAYERZNEG_1);
			update_pos_array(ID_LAYERZNEG_2);
			break;
		case ID_ZPOS:
			update_pos_array(ID_LAYERZPOS_0);
			update_pos_array(ID_LAYERZPOS_1);
			update_pos_array(ID_LAYERZPOS_2);
			break;

		/***** Z POS *****/
		case ID_LAYERZPOS_0:
			pos[ 0] = copy[ 2]; pos[ 1] = copy[ 5]; pos[ 2] = copy[ 8];
			pos[ 3] = copy[ 1]; pos[ 4] = copy[ 4]; pos[ 5] = copy[ 7];
			pos[ 6] = copy[ 0]; pos[ 7] = copy[ 3]; pos[ 8] = copy[ 6];
			break;
		case ID_LAYERZPOS_1:
			pos[ 9] = copy[11]; pos[10] = copy[14]; pos[11] = copy[17];
			pos[12] = copy[10]; pos[13] = copy[13]; pos[14] = copy[16];
			pos[15] = copy[ 9]; pos[16] = copy[12]; pos[17] = copy[15];
			break;
		case ID_LAYERZPOS_2:
			pos[18] = copy[20]; pos[19] = copy[23]; pos[20] = copy[26];
			pos[21] = copy[19]; pos[22] = copy[22]; pos[23] = copy[25];
			pos[24] = copy[18]; pos[25] = copy[21]; pos[26] = copy[24];
			break;

		/***** ZNEG *****/
		case ID_LAYERZNEG_0:
			pos[ 0] = copy[ 6]; pos[ 1] = copy[ 3]; pos[ 2] = copy[ 0];
			pos[ 3] = copy[ 7]; pos[ 4] = copy[ 4]; pos[ 5] = copy[ 1];
			pos[ 6] = copy[ 8]; pos[ 7] = copy[ 5]; pos[ 8] = copy[ 2];
			break;
		case ID_LAYERZNEG_1:
			pos[ 9] = copy[15]; pos[10] = copy[12]; pos[11] = copy[ 9];
			pos[12] = copy[16]; pos[13] = copy[13]; pos[14] = copy[10];
			pos[15] = copy[17]; pos[16] = copy[14]; pos[17] = copy[11];
			break;
		case ID_LAYERZNEG_2:
			pos[18] = copy[24]; pos[19] = copy[21]; pos[20] = copy[18];
			pos[21] = copy[25]; pos[22] = copy[22]; pos[23] = copy[19];
			pos[24] = copy[26]; pos[25] = copy[23]; pos[26] = copy[20];
			break;

		/***** YPOS *****/
		case ID_LAYERYPOS_0:
			pos[ 0] = copy[18]; pos[ 1] = copy[ 9]; pos[ 2] = copy[ 0];
			pos[ 9] = copy[19]; pos[10] = copy[10]; pos[11] = copy[ 1];
			pos[18] = copy[20]; pos[19] = copy[11]; pos[20] = copy[ 2];
			break;
		case ID_LAYERYPOS_1:
			pos[ 3] = copy[21]; pos[ 4] = copy[12]; pos[ 5] = copy[ 3];
			pos[12] = copy[22]; pos[13] = copy[13]; pos[14] = copy[ 4];
			pos[21] = copy[23]; pos[22] = copy[14]; pos[23] = copy[ 5];
			break;
		case ID_LAYERYPOS_2:
			pos[ 6] = copy[24]; pos[ 7] = copy[15]; pos[ 8] = copy[ 6];
			pos[15] = copy[25]; pos[16] = copy[16]; pos[17] = copy[ 7];
			pos[24] = copy[26]; pos[25] = copy[17]; pos[26] = copy[ 8];
			break;

		/***** YNEG *****/
		case ID_LAYERYNEG_0:
			pos[ 0] = copy[ 2]; pos[ 1] = copy[11]; pos[ 2] = copy[20];
			pos[ 9] = copy[ 1]; pos[10] = copy[10]; pos[11] = copy[19];
			pos[18] = copy[ 0]; pos[19] = copy[ 9]; pos[20] = copy[18];
			break;
		case ID_LAYERYNEG_1:
			pos[ 3] = copy[ 5]; pos[ 4] = copy[14]; pos[ 5] = copy[23];
			pos[12] = copy[ 4]; pos[13] = copy[13]; pos[14] = copy[22];
			pos[21] = copy[ 3]; pos[22] = copy[12]; pos[23] = copy[21];
			break;
		case ID_LAYERYNEG_2:
			pos[ 6] = copy[ 8]; pos[ 7] = copy[17]; pos[ 8] = copy[26];
			pos[15] = copy[ 7]; pos[16] = copy[16]; pos[17] = copy[25];
			pos[24] = copy[ 6]; pos[25] = copy[15]; pos[26] = copy[24];
			break;

		default:
			break;
	}
}

void multiply_unit_matrices(int move_id)
{
	int i, j;

	switch (move_id) {

		/***** VIEW ROTATIONS *****/

			/* Multiplying all unit cubes in this case, since all of them are
			   affected by view change */
		case ID_YNEG:
			for (i = 0; i < UNIT_CUBE_NUM; i++)
				multiply_matrices(Y_NEG_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_YPOS:
			for (i = 0; i < UNIT_CUBE_NUM; i++)
				multiply_matrices(Y_POS_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_ZNEG:
			for (i = 0; i < UNIT_CUBE_NUM; i++)
				multiply_matrices(Z_NEG_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_ZPOS:
			for (i = 0; i < UNIT_CUBE_NUM; i++)
				multiply_matrices(Z_POS_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;

		/***** Z LAYER ROTATIONS *****/

			/* Multiplying unit cubes at left vertical layer position */
		case ID_LAYERZPOS_0:
			for (i = 0; i < UNITS_IN_LAYER; i++)
				multiply_matrices(Z_POS_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_LAYERZNEG_0:
			for (i = 0; i < UNITS_IN_LAYER; i++)
				multiply_matrices(Z_NEG_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;

			/* Multiplying unit cubes at middle vertical layer position */
		case ID_LAYERZPOS_1:
			for (i = UNITS_IN_LAYER; i < 2 * UNITS_IN_LAYER; i++)
				multiply_matrices(Z_POS_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_LAYERZNEG_1:
			for (i = UNITS_IN_LAYER; i < 2 * UNITS_IN_LAYER; i++)
				multiply_matrices(Z_NEG_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;

			/* Multiplying unit cubes at right vertical layer position */
		case ID_LAYERZPOS_2:
			for (i = 2 * UNITS_IN_LAYER; i < 3 * UNITS_IN_LAYER; i++)
				multiply_matrices(Z_POS_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_LAYERZNEG_2:
			for (i = 2 * UNITS_IN_LAYER; i < 3 * UNITS_IN_LAYER; i++)
				multiply_matrices(Z_NEG_ROT_MATRIX, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;

		/***** Z LAYER ROTATIONS *****/

			/* Multiplying unit cubes at top horizontal layer position */
		case ID_LAYERYPOS_0:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 0; j < 3; j++)
					multiply_matrices(Y_POS_ROT_MATRIX, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;
		case ID_LAYERYNEG_0:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 0; j < 3; j++)
					multiply_matrices(Y_NEG_ROT_MATRIX, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;

			/* Multiplying unit cubes at middle horizontal layer position */
		case ID_LAYERYPOS_1:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 3; j < 6; j++)
					multiply_matrices(Y_POS_ROT_MATRIX, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;
		case ID_LAYERYNEG_1:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 3; j < 6; j++)
					multiply_matrices(Y_NEG_ROT_MATRIX, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;

			/* Multiplying unit cubes at bottom horizontal layer position */
		case ID_LAYERYPOS_2:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 6; j < 9; j++)
					multiply_matrices(Y_POS_ROT_MATRIX, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;
		case ID_LAYERYNEG_2:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 6; j < 9; j++)
					multiply_matrices(Y_NEG_ROT_MATRIX, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;
	}
}

/* Same as multiply_unit_matrices, except here we use 90 degree matrices */
void multiply_unit_matrices_full(int move_id)
{
	int i, j;

	switch (move_id) {

		/***** VIEW ROTATIONS *****/

			/* Multiplying all unit cubes */
		case ID_YNEG:
			for (i = 0; i < UNIT_CUBE_NUM; i++)
				multiply_matrices(Y_NEG_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_YPOS:
			for (i = 0; i < UNIT_CUBE_NUM; i++)
				multiply_matrices(Y_POS_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_ZNEG:
			for (i = 0; i < UNIT_CUBE_NUM; i++)
				multiply_matrices(Z_NEG_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_ZPOS:
			for (i = 0; i < UNIT_CUBE_NUM; i++)
				multiply_matrices(Z_POS_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;

		/***** Z LAYER ROTATIONS *****/

			/* Multiplying unit cubes at left vertical layer position */
		case ID_LAYERZPOS_0:
			for (i = 0; i < UNITS_IN_LAYER; i++)
				multiply_matrices(Z_POS_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_LAYERZNEG_0:
			for (i = 0; i < UNITS_IN_LAYER; i++)
				multiply_matrices(Z_NEG_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;

			/* Multiplying unit cubes at middle vertical layer position */
		case ID_LAYERZPOS_1:
			for (i = UNITS_IN_LAYER; i < 2 * UNITS_IN_LAYER; i++)
				multiply_matrices(Z_POS_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_LAYERZNEG_1:
			for (i = UNITS_IN_LAYER; i < 2 * UNITS_IN_LAYER; i++)
				multiply_matrices(Z_NEG_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;

			/* Multiplying unit cubes at right vertical layer position */
		case ID_LAYERZPOS_2:
			for (i = 2 * UNITS_IN_LAYER; i < 3 * UNITS_IN_LAYER; i++)
				multiply_matrices(Z_POS_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;
		case ID_LAYERZNEG_2:
			for (i = 2 * UNITS_IN_LAYER; i < 3 * UNITS_IN_LAYER; i++)
				multiply_matrices(Z_NEG_ROT_MATRIX_FULL, rotate_matrix[pos[i]],
					rotate_matrix[pos[i]]);
			break;

		/***** Z LAYER ROTATIONS *****/

			/* Multiplying unit cubes at top horizontal layer position */
		case ID_LAYERYPOS_0:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 0; j < 3; j++)
					multiply_matrices(Y_POS_ROT_MATRIX_FULL, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;
		case ID_LAYERYNEG_0:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 0; j < 3; j++)
					multiply_matrices(Y_NEG_ROT_MATRIX_FULL, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;

			/* Multiplying unit cubes at middle horizontal layer position */
		case ID_LAYERYPOS_1:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 3; j < 6; j++)
					multiply_matrices(Y_POS_ROT_MATRIX_FULL, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;
		case ID_LAYERYNEG_1:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 3; j < 6; j++)
					multiply_matrices(Y_NEG_ROT_MATRIX_FULL, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;

			/* Multiplying unit cubes at bottom horizontal layer position */
		case ID_LAYERYPOS_2:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 6; j < 9; j++)
					multiply_matrices(Y_POS_ROT_MATRIX_FULL, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;
		case ID_LAYERYNEG_2:
			for (i = 0; i < UNIT_CUBE_NUM; i += UNITS_IN_LAYER)
				for (j = 6; j < 9; j++)
					multiply_matrices(Y_NEG_ROT_MATRIX_FULL, rotate_matrix[pos[i+j]],
						rotate_matrix[pos[i+j]]);
			break;
	}
}
