/*
	This file contains functions that are passed to glut, to be used when
	a certain event happens (such as mouse click or keyborad hit).
*/

#ifndef _H_CALLBACKS_H_
#define _H_CALLBACKS_H_

#include <stdlib.h>
#include <GL/glut.h>
#include "draw.h"
#include "init.h"
#include "indicators.h"
#include "matrices.h"
#include "moves.h"
#include "rand.h"
#include "gui.h"
#include "textures.h"
#include "timers.h"


/* Display change handler */
void on_display(void);

/* Window resize handler */
void on_reshape(int width, int height);

/* Keyboard press handler */
void on_keyboard(unsigned char key, int mouse_x, int mouse_y);

/* Mouse click handler */
void on_mouse(int button, int state, int x, int y);

/* Functions called by on_mouse function, for rotating view and layers */
void rotate_view(int dx, int dy);
void rotate_layer(int x, int y, int dx, int dy);


#endif
