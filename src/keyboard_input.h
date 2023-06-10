#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <curses.h>
#include <ctype.h>

#include "data_structures.h"
#include "screen.h"
#include "config.h"

/* Declarations */
void handle_input(WINDOW* wnd, map_s* map, entity_s* entity_list, char* c);


#endif /* KEYBOARD_INPUT_H */