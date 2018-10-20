#include "include/moves.h"


/* Initially there are no moves in list */
Move *move_list = NULL;


void add_to_movelist(int move_id)
{
	/* If we had an error previously, we won't do anything */
	if (ERR_INDICATOR == 1)
		return;

	/* Creating new move */
	Move *new = (Move*)malloc(sizeof(Move));

	/* If allocation failed, program will keep running but it will not allow
	   access to move_list in future */
	if (new == NULL) {
		ERR_INDICATOR = 1;
		return;
	}

	/* Copying data to successfully allocated struct */
	new->id = move_id;
	new->next = move_list;
	move_list = new;
}

void undo_move(void)
{
	/* In case of error or an empty list, there is no move to undo */
	if (ERR_INDICATOR == 1 || move_list == NULL)
		return;

	/* Performing reverse rotation, based on rotation ID
	   (but not adding it to move_list) */
	switch (move_list->id) {
		case ID_YNEG:
			on_timer(ID_YPOS, 0);
			break;
		case ID_YPOS:
			on_timer(ID_YNEG, 0);
			break;
		case ID_ZNEG:
			on_timer(ID_ZPOS, 0);
			break;
		case ID_ZPOS:
			on_timer(ID_ZNEG, 0);
			break;
		case ID_LAYERZPOS_0:
			on_timer(ID_LAYERZNEG_0, 0);
			break;
		case ID_LAYERZPOS_1:
			on_timer(ID_LAYERZNEG_1, 0);
			break;
		case ID_LAYERZPOS_2:
			on_timer(ID_LAYERZNEG_2, 0);
			break;
		case ID_LAYERZNEG_0:
			on_timer(ID_LAYERZPOS_0, 0);
			break;
		case ID_LAYERZNEG_1:
			on_timer(ID_LAYERZPOS_1, 0);
			break;
		case ID_LAYERZNEG_2:
			on_timer(ID_LAYERZPOS_2, 0);
			break;
		case ID_LAYERYPOS_0:
			on_timer(ID_LAYERYNEG_0, 0);
			break;
		case ID_LAYERYPOS_1:
			on_timer(ID_LAYERYNEG_1, 0);
			break;
		case ID_LAYERYPOS_2:
			on_timer(ID_LAYERYNEG_2, 0);
			break;
		case ID_LAYERYNEG_0:
			on_timer(ID_LAYERYPOS_0, 0);
			break;
		case ID_LAYERYNEG_1:
			on_timer(ID_LAYERYPOS_1, 0);
			break;
		case ID_LAYERYNEG_2:
			on_timer(ID_LAYERYPOS_2, 0);
			break;
			
		default:
			return;
	}

	/* Removing last move from list */
	Move *new_top = move_list->next;
	free(move_list);
	move_list = new_top;
}

void free_movelist(void)
{
	/* Freeing list */
	while (move_list != NULL) {
		Move *new_top = move_list->next;
		free(move_list);
		move_list = new_top;
	}

	/* Placing NULL inside, just in case */
	move_list = NULL;
}
