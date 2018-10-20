/*
	This file contains timers that are triggered by callback functions.
	These timers perform rotations by multiplicating saved unit cube matrices
	with rotation matrices.
*/

#ifndef _H_TIMERS_H_
#define _H_TIMERS_H_

#include <GL/glut.h>
#include "indicators.h"
#include "matrices.h"
#include "moves.h"


/* Time in ms between timer ticks */
#define TIMER_INTERVAL 15

/* For each pressed key, timer is called 18 times which we define as ITER_NUM.
   Since the rotation angle step is 5 degrees, 5*18 = 90 */
#define ITER_NUM 18


/* Increments rotation_ticker and checks if it has reached ITER_NUM
   If it did, rotation_ticker and rotation_running are set to 0 */
void increment_ticker(void);

/* Wrapper for timer tick function.
   add_move_ind determines if we should add the move into the list or not */
void on_timer(int timer_id, int add_move_ind);

/* Timer tick function, performing unit rotations for 5 degrees at a time */
void timer_tick(int timer_id);

/* Timer tick function, performing unit rotations immediately */
void timer_tick_full(int timer_id);


#endif
