#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <curses.h>
#include <ctype.h>
#include "data_structures.h"

/* Global */
extern state game_state;
extern int X, Y;

/* Declarations */

void draw(char c);
void draw_play_area(int X, int Y);
void handle_input(WINDOW* wnd, position* xy, char* c);
void move_char(position* xy, direction dir);
void calculate_movement(position* xy, position* xy_new, direction dir);
bool validate_movement(position* xy);
void debug(WINDOW* wnd, position xy, char* msg);

#endif /* MOVEMENT_H */