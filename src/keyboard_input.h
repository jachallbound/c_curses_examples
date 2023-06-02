#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <curses.h>
#include <ctype.h>

#include "data_structures.h"
#include "screen.h"

/* Global */
extern state game_state;


/* Declarations */
void handle_input(WINDOW* wnd, position* xy, char* c);
void move_char(position* xy, direction dir);
void calculate_movement(position* xy, position* xy_new, direction dir);
bool validate_movement(position* xy);


#endif /* KEYBOARD_INPUT_H */