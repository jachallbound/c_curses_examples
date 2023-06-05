#ifndef SCREEN_H
#define SCREEN_H

#include <curses.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "data_structures.h"
#include "data_input.h"
#include "keyboard_input.h"

/* Declarations */
void draw(char c);
void draw_at_position(char c, position xyz);
void display_message(WINDOW* wnd, map_s* map, position xy, char* msg);
state change_map(map_s* map, position* xy);

/* Sleep function */
int msleep(long msec);

/* Depricated */
void draw_play_area(int X, int Y);


#endif /* SCREEN_H */