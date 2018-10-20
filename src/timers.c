#include "include/timers.h"


/* Tick counter - we will call a certain timer exactly ITER_NUM times */
static int rotation_ticker = 0;


void increment_ticker(void)
{
	/* Incrementing and checking if we did ITER_NUM rotations */
	rotation_ticker++;
	if (rotation_ticker == ITER_NUM)
		rotation_running = rotation_ticker = 0;
}

void on_timer(int timer_id, int add_move_ind)
{
	if (rotation_running)
		return;

	rotation_running = 1;

	/* Calling our timer_tick function, depending of speed_mode indicator */
	if (speed_mode_on)
		glutTimerFunc(TIMER_INTERVAL, &timer_tick_full, timer_id);
	else
		glutTimerFunc(TIMER_INTERVAL, &timer_tick, timer_id);

	/* Adding rotation ID (timer_id) in our move list, if we are instructed to do so */
	if (add_move_ind)
		add_to_movelist(timer_id);

	/* Updating position array, based on rotation ID (timer_id) */
	update_pos_array(timer_id);
}

void timer_tick(int timer_id)
{
	/* Multiply corresponding unit matrices */
	multiply_unit_matrices(timer_id);

	/* Incrementing our step ticker */
	increment_ticker();

	/* Redrawing scene */
	glutPostRedisplay();

	/* Calling again, if ticker did not reach ITER_NUM */
	if (rotation_running)
		glutTimerFunc(TIMER_INTERVAL, &timer_tick, timer_id);
}

void timer_tick_full(int timer_id)
{
	/* Multiply corresponding unit matrices */
	multiply_unit_matrices_full(timer_id);

	/* Resetting indicator and ticker */
	rotation_running = rotation_ticker = 0;

	/* Redrawing scene */
	glutPostRedisplay();
}
