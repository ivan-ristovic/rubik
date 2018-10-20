#include "include/rand.h"


void randomize_cube(int num_iter)
{
	printf("Randomizing cube... ");
	fflush(stdout);
	randomization_running = 1;

	/* Performing random move num_iter times */
	int i;
	for (i = 0; i < num_iter; i++)
		perform_random_move(i);

	/* Re-drawing scene */
	glutPostRedisplay();

	printf("Done!\n");
	fflush(stdout);
	randomization_running = 0;
}

void perform_random_move(unsigned seed)
{
	/* Generating random number for our rotation ID */
	srand(seed + time(NULL));
	int move_id = rand() % MOVE_NUM;

	/* Deciding which rotation this is, doing matrix multiplication and
	   updating position array */
	switch (move_id) {
		case  0:
			multiply_unit_matrices_full(ID_YPOS);
			update_pos_array(ID_YPOS);
			break;
		case  1:
			multiply_unit_matrices_full(ID_YNEG);
			update_pos_array(ID_YNEG);
			break;
		case  2:
			multiply_unit_matrices_full(ID_ZPOS);
			update_pos_array(ID_ZPOS);
			break;
		case  3:
			multiply_unit_matrices_full(ID_ZNEG);
			update_pos_array(ID_ZNEG);
			break;
		case  4:
			multiply_unit_matrices_full(ID_LAYERZPOS_0);
			update_pos_array(ID_LAYERZPOS_0);
			break;
		case  5:
			multiply_unit_matrices_full(ID_LAYERZPOS_1);
			update_pos_array(ID_LAYERZPOS_1);
			break;
		case  6:
			multiply_unit_matrices_full(ID_LAYERZPOS_2);
			update_pos_array(ID_LAYERZPOS_2);
			break;
		case  7:
			multiply_unit_matrices_full(ID_LAYERZNEG_0);
			update_pos_array(ID_LAYERZNEG_0);
			break;
		case  8:
			multiply_unit_matrices_full(ID_LAYERZNEG_1);
			update_pos_array(ID_LAYERZNEG_1);
			break;
		case  9:
			multiply_unit_matrices_full(ID_LAYERZNEG_2);
			update_pos_array(ID_LAYERZNEG_2);
			break;
		case 10:
			multiply_unit_matrices_full(ID_LAYERYPOS_0);
			update_pos_array(ID_LAYERYPOS_0);
			break;
		case 11:
			multiply_unit_matrices_full(ID_LAYERYPOS_1);
			update_pos_array(ID_LAYERYPOS_1);
			break;
		case 12:
			multiply_unit_matrices_full(ID_LAYERYPOS_2);
			update_pos_array(ID_LAYERYPOS_2);
			break;
		case 13:
			multiply_unit_matrices_full(ID_LAYERYNEG_0);
			update_pos_array(ID_LAYERYNEG_0);
			break;
		case 14:
			multiply_unit_matrices_full(ID_LAYERYNEG_1);
			update_pos_array(ID_LAYERYNEG_1);
			break;
		case 15:
			multiply_unit_matrices_full(ID_LAYERYNEG_2);
			update_pos_array(ID_LAYERYNEG_2);
			break;
	}
}
