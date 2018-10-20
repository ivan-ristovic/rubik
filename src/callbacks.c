#include "include/callbacks.h"


void on_display(void)
{
	/* Clearing previous scene */
	glClearColor(.7, .7, .7, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Rendering GUI elements */
	if (show_fps)
		print_fps();
	if (speed_mode_on)
		print_speedmode_indicator();
	print_time();

	/* Switching to MODEL_VIEW matrix mode */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Positioning camera */
	gluLookAt(7, 3, 3, 0, 0, 0, 0, 1, 0);

	/* Drawing background */
	draw_background();

	/* Drawing cube */
	draw_rubik_cube(0, 0, 0);

	/* Swapping buffers */
	glutSwapBuffers();
}

void on_reshape(int width, int height)
{
	int size = min(width, height);

	/* If new window is smaller than minimum size window, resize */
	if (size < MIN_WINDOW_SIZE) {
		glutReshapeWindow(MIN_WINDOW_SIZE, MIN_WINDOW_SIZE);
		return;
	}

	/* Reshaping to force square window */
	glutReshapeWindow(size, size);

	/* Setting viewport */
	glViewport(0, 0, size, size);

	/* Setting perspective parameters */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 30);
}

void on_keyboard(unsigned char key, int mouse_x, int mouse_y)
{
	/* Processing pressed key */
	switch (key) {
		case 'Q':	/* Exit program */
		case 'q':
		case 27:	/* ESC ASCII code is 27 */
			free_resources();
			exit(EXIT_SUCCESS);
			break;
		case 'R':	/* Reset cube to a solved state */
		case 'r':
			initialize_matrices();
			free_resources();
			glutPostRedisplay();
			break;
		case 'T':	/* Randomize cube */
		case 't':
			if (!randomization_running)
				randomize_cube(RANDOMIZATION_STEPS_NUM);
			break;
		case 'U':	/* Undo move */
		case 'u':
			undo_move();
			break;
		case 'E':	/* Toggle speed mode */
		case 'e':
			speed_mode_on = !speed_mode_on;
			break;
		case 'F':	/* Toggle fps display */
		case 'f':
			show_fps = !show_fps;
			break;
		case ' ':	/* Start/Stop stopwatch */
			stopwatch_running = !stopwatch_running;
			break;

	/***** CUBE VIEW ROTATION CASES *****/

		case 'A':	/* Rotate cube around Y axis, negative direction */
		case 'a':
			on_timer(ID_YNEG, 1);
			break;
		case 'D':	/* Rotate cube around Y axis, positive direction */
		case 'd':
			on_timer(ID_YPOS, 1);
			break;
		case 'W':	/* Rotate cube around Z axis, negative direction */
		case 'w':
			on_timer(ID_ZNEG, 1);
			break;
		break;
		case 'S':	/* Rotate cube around Z axis, positive direction */
		case 's':
			on_timer(ID_ZPOS, 1);
			break;

	/***** Z LAYERS ROTATION CASES *****/

		case 'z':	/* Rotate 1st vertical layer from left, positive direction */
			on_timer(ID_LAYERZPOS_0, 1);
			break;
		case 'x':	/* Rotate 2nd vertical layer from left, positive direction */
			on_timer(ID_LAYERZPOS_1, 1);
			break;
		case 'c':	/* Rotate 3rd vertical layer from left, positive direction */
			on_timer(ID_LAYERZPOS_2, 1);
			break;
		case 'Z':	/* Rotate 1st vertical layer from left, negative direction */
			on_timer(ID_LAYERZNEG_0, 1);
			break;
		case 'X':	/* Rotate 2nd vertical layer from left, negative direction */
			on_timer(ID_LAYERZNEG_1, 1);
			break;
		case 'C':	/* Rotate 3rd vertical layer from left, negative direction */
			on_timer(ID_LAYERZNEG_2, 1);
			break;

	/***** Y LAYERS ROTATION CASES *****/

		case 'v':	/* Rotate 1st horizontal layer, positive direction */
			on_timer(ID_LAYERYPOS_0, 1);
			break;
		case 'b':	/* Rotate 2nd horizontal layer, positive direction */
			on_timer(ID_LAYERYPOS_1, 1);
			break;
		case 'n':	/* Rotate 3rd horizontal layer, positive direction */
			on_timer(ID_LAYERYPOS_2, 1);
			break;
		case 'V':	/* Rotate 1st horizontal layer, negative direction */
			on_timer(ID_LAYERYNEG_0, 1);
			break;
		case 'B':	/* Rotate 2nd horizontal layer, negative direction */
			on_timer(ID_LAYERYNEG_1, 1);
			break;
		case 'N':	/* Rotate 3rd horizontal layer, negative direction */
			on_timer(ID_LAYERYNEG_2, 1);
			break;

		default:
			break;
	}
}


/* When mouse is clicked, mouse coordinates are saved here */
static int startx, starty;
/* Allowed drag error */
static int eps = 20;
/* Minimum required drag length for control to be accepted */
static int min_drag = 20;

void on_mouse(int button, int state, int x, int y)
{
	/* If mouse is pressed, saving starting coordinates */
	if (state == GLUT_DOWN) {
		startx = x;
		starty = y;
		return;
	}

	/* Otherwise, calculating difference in coordinates */
	int deltax = x - startx;
	int deltay = y - starty;

	/* If that difference is below than min_drag, it means user didn't move
	   mouse far enough to trigger a move, and the input is rejected */
	if (abs(deltax) < min_drag && abs(deltay) < min_drag)
		return;

	/* If everything passed, checking if user wants to rotate view or layer,
	   which depends of left/right click */
	switch (button) {
		case GLUT_LEFT_BUTTON:
			rotate_layer(startx, starty, deltax, deltay);
			break;
		case GLUT_RIGHT_BUTTON:
			rotate_view(deltax, deltay);
			break;
		default:
			return;
	}
}

void rotate_view(int dx, int dy)
{
	if (rotation_running)
		return;

	/* Deciding drag direction, allowing error to be eps at most */
	if (dx < 0 && abs(dy) < eps)
		on_timer(ID_YPOS, 1);
	else if (dx > 0 && abs(dy) < eps)
		on_timer(ID_YNEG, 1);
	else if (dy < 0 && abs(dx) < eps)
		on_timer(ID_ZNEG, 1);
	else if (dy > 0 && abs(dx) < eps)
		on_timer(ID_ZPOS, 1);
	else
		rotation_running = 0;
}

void rotate_layer(int x, int y, int dx, int dy)
{
	if (rotation_running)
		return;

	/* The size of one layer, roughly windowsize / 8 */
	int size = glutGet(GLUT_WINDOW_WIDTH) / 8;
	int size3 = 3 * size, size4 = 4 * size, size5 = 5 * size, size6 = 6 * size;


	/* Deciding which layer to rotate */
	if (dx < 0 && abs(dy) < eps) {		/* if user dragged left */
		/* Deciding which layer was selected */
		if (y > size3 && y < size4)
			on_timer(ID_LAYERYPOS_0, 1);
		else if (y >= size4 && y < size5)
			on_timer(ID_LAYERYPOS_1, 1);
		else if (y >= size5 && y < size6)
			on_timer(ID_LAYERYPOS_2, 1);
		else
			rotation_running = 0;
	}
	else if (dx > 0 && abs(dy) < eps) {		/* If user dragged right */
		/* Deciding which layer was selected */
		if (y > size3 && y < size4)
			on_timer(ID_LAYERYNEG_0, 1);
		else if (y >= size4 && y < size5)
			on_timer(ID_LAYERYNEG_1, 1);
		else if (y >= size5 && y < size6)
			on_timer(ID_LAYERYNEG_2, 1);
		else
			rotation_running = 0;
	}
	else if (dy < 0 && abs(dx) < eps) {		/* If user dragged up */
		/* Deciding which layer was selected */
		if (x > size3 && x < size4)
			on_timer(ID_LAYERZNEG_0, 1);
		else if (x >= size4 && x < size5)
			on_timer(ID_LAYERZNEG_1, 1);
		else if (x >= size5 && x < size6)
			on_timer(ID_LAYERZNEG_2, 1);
		else
			rotation_running = 0;
	}
	else if (dy > 0 && abs(dx) < eps) {		/* If user dragged down */
		/* Deciding which layer was selected */
		if (x > size3 && x < size4)
			on_timer(ID_LAYERZPOS_0, 1);
		else if (x >= size4 && x < size5)
			on_timer(ID_LAYERZPOS_1, 1);
		else if (x >= size5 && x < size6)
			on_timer(ID_LAYERZPOS_2, 1);
		else
		 	rotation_running = 0;
	}
	else	/* If the error was greater than eps, we do nothing */
		rotation_running = 0;
}
