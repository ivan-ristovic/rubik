/*
	This file contains functions that work with performed moves. They are saved
	in a list, placing each new move on start of the list.
*/

#ifndef _H_MOVES_H_
#define _H_MOVES_H_

#include <stdlib.h>
#include "indicators.h"
#include "timers.h"


/* Struct representing a single move */
typedef struct _move {
	int id;
	struct _move *next;
} Move;


/* List of all performed moves so far */
extern Move *move_list;


/* Puts a move in the move list */
void add_to_movelist(int move_id);

/* Removes last performed move from list, performing reverse rotation */
void undo_move(void);

/* Free moves list */
void free_movelist(void);


#endif
