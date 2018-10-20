/*
	This file contains stopwatch functions - printing elapsed time and
	FPS to stdout.
*/

#ifndef _H_GUI_H_
#define _H_GUI_H_

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "indicators.h"


/* Number of milliseconds in one second */
#define SECOND 1000

/* Values that trigger FPS color change */
#define GOOD_FPS	150
#define MEDIUM_FPS	 60


/* updates time difference between two consequent calls */
void update_time_diff(void);

/* Prints current elapsed time */
void print_time(void);

/* Prints FPS */
void print_fps(void);

/* Prints speed mode indicator */
void print_speedmode_indicator(void);

/* Renders string at position (x, y, z) using provided font and (r, g, b) color */
void render_string_at( float x, float y, float z, float r, float g, float b,
	void *font, const char* string
);


#endif
