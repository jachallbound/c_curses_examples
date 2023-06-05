#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <curses.h>
#include <ctype.h>

#include "data_structures.h"
#include "screen.h"

/* Declarations */
void handle_input(WINDOW* wnd, map_s* map, position* xy, char* c);


#endif /* KEYBOARD_INPUT_H */