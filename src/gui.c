#include "include/gui.h"


/* Variables that help calculate time_difference (for fps) */
static int new_time;
static int old_time = 0;

/* Current fps */
static int fps = 0;

/* FPS string (to be rendered) */
static char fps_str[] = "  0 FPS";


void print_fps(void)
{
	/* Printing FPS string: red means worse, while means great */
	if (fps >= GOOD_FPS)
		render_string_at(-4, 4, 3.5, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, fps_str);
	else if (fps >= MEDIUM_FPS)
		render_string_at(-4, 4, 3.5, 1, 1, 0, GLUT_BITMAP_HELVETICA_18, fps_str);
	else
		render_string_at(-4, 4, 3.5, 1, 0, 0, GLUT_BITMAP_HELVETICA_18, fps_str);

	/* Frame counter */
	static int frame_count = 0;
	frame_count++;

	/* Reading new time */
	new_time = glutGet(GLUT_ELAPSED_TIME);
	int time_diff = new_time - old_time;

	/* If difference is greater than one second, update fps_str */
	if (time_diff >= SECOND) {
		fps = frame_count * SECOND / time_diff;
		sprintf(fps_str, "%3d FPS", fps);
		frame_count = 0;
		old_time = new_time;
	}
}


/* Time recorded when stopwatch is started */
static int stopw_start_time = 0;

/* Previous recorded time in each iteration */
static int prev_time = 0;

/* Time string (to be rendered) */
char time_str[] = "00m:00s";


void print_time(void)
{
	/* Printing time_string, green if stopwatch is running */
	if (stopwatch_running)
		render_string_at(-2, -8, 0, 0, 1, 0, GLUT_BITMAP_HELVETICA_18, time_str);
	else
		render_string_at(-2, -8, 0, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, time_str);

	/* If stopwatch is not running, we will not print anything */
	if (!stopwatch_running) {
		stopw_start_time = prev_time = 0;
		return;
	}

	/* If stopw_start_time has default value, it means that stopwatch was
	   started now, so we will set stopw_start_time to current elapsed time */
	if (stopw_start_time == 0)
		stopw_start_time = glutGet(GLUT_ELAPSED_TIME);

	/* Calculating time difference */
	int current_time = glutGet(GLUT_ELAPSED_TIME);
	int diff = current_time - stopw_start_time;

	/* If that difference is greater than prev_time, and difference between them
	   is atleast one second, then we update time_str and prev_time */
	if (diff >= prev_time + SECOND) {
		int seconds = diff / SECOND;
		sprintf(time_str, "%02dm:%02ds", seconds / 60, seconds % 60);
		prev_time = diff;
	}
}

void print_speedmode_indicator(void)
{
	render_string_at(-4, 3, 3.5, 0, 1, 0, GLUT_BITMAP_HELVETICA_18, "S");
}

void render_string_at(float x, float y, float z, float r, float g, float b,
	void *font, const char* string)
{
	/* Setting emission coefficients for our font material */
	GLfloat emission_coeffs[] = { r, g, b, 1 };

	glMaterialfv(GL_FRONT, GL_EMISSION, emission_coeffs);

	/* Setting raster position to given point */
	glRasterPos3f(x, y, z);

	/* Rendering string */
	glutBitmapString(font, (const unsigned char*)string);

	/* Removing emission coefficients for other materials */
	GLfloat emission_coeffs_reset[] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_coeffs_reset);
}
