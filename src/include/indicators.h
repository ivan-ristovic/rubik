/*
	This file contains rotation indicators, which help determine which rotation
	was triggered. These indicators are used also for remembering perfomed moves,
	since all we need to do in that case is to remember these IDs in a list.
*/

#ifndef _H_INDICATORS_H_
#define _H_INDICATORS_H_


/* All variables below are initialized to zero in init.c */

/* Error indicator */
extern int ERR_INDICATOR;

/* Stopwatch running indicator */
extern int stopwatch_running;

/* Show fps indicator */
extern int show_fps;

/* Speed mode indicator */
extern int speed_mode_on;

/* Animation running indicator */
extern int rotation_running;

/* Randomization running indicator */
extern int randomization_running;


/* Rotation indicators */
enum rotation_id {
	ID_YPOS,        	/* view-y, positive (right) */
	ID_YNEG,        	/* view-y, negative (left) */
	ID_ZPOS,        	/* view-z, positive (down) */
	ID_ZNEG,        	/* view-z, negative (up) */
	ID_LAYERZPOS_0, 	/* left vertical layer, down */
	ID_LAYERZPOS_1, 	/* middle vertical layer, down */
	ID_LAYERZPOS_2, 	/* right vertical layer, down */
	ID_LAYERZNEG_0, 	/* left vertical layer, up */
	ID_LAYERZNEG_1, 	/* middle vertical layer, up */
	ID_LAYERZNEG_2, 	/* right vertical layer, up */
	ID_LAYERYPOS_0, 	/* top horizontal layer, left */
	ID_LAYERYPOS_1, 	/* middle horizontal layer, left */
	ID_LAYERYPOS_2, 	/* bottom horizontal layer, left */
	ID_LAYERYNEG_0, 	/* top horizontal layer, right */
	ID_LAYERYNEG_1, 	/* middle horizontal layer, right */
	ID_LAYERYNEG_2  	/* bottom horizontal layer, right */
};

#endif
