#include "include/init.h"


/* Initializing all indicators */
int ERR_INDICATOR = 0;
int speed_mode_on;
int show_fps = 0;
int randomization_running = 0;
int rotation_running = 0;
int stopwatch_running = 0;


void initialize_callbacks(void)
{
	glutDisplayFunc(&on_display);
	glutKeyboardFunc(&on_keyboard);
	glutReshapeFunc(&on_reshape);
	glutMouseFunc(&on_mouse);
	atexit(&free_resources);
}

void initialize_glut(int *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	/* Creating window */
	glutInitWindowSize(INIT_WINDOW_SIZE, INIT_WINDOW_SIZE);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Rubik's Cube");
	glutSetIconTitle("Rubik's Cube");

	glEnable(GL_DEPTH_TEST);
}

void initialize_light()
{
	/* Enabling lighting */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* Defining light components */
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat light_diffuse[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	/* Material parameters */
	GLfloat shiness = 40;
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);

	/* Setting light position */
	GLfloat light_position[] = { 0, 2, 0, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void initialize_matrices(void)
{
	/* Loading identity matrices in unit cube rotation matrices */
	int i;
	for (i = 0; i < UNIT_CUBE_NUM; i++) {
		load_id_matrix(rotate_matrix[i]);
		/* While we are doing that, initializing position array as well */
		pos[i] = i;
	}
}

void initialize_textures(void)
{
	/* Enabling texture mode */
	glEnable(GL_TEXTURE_2D);

	/* Loading background texture in bg_tex_ptr */
	load_background_texture("tex/bg.bmp");

	/* Loading textures for unit cubes in side_tex_ptr */
	load_unit_texture();
}

void free_resources(void)
{
	/* Freeing list of all performed moves */
	free_movelist();
}
