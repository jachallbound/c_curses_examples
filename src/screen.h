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
void update_map(WINDOW* wnd, const map_s* map, entity_s* entity_list);
void display_message(WINDOW* wnd, const map_s* map, char* msg);

state change_map(map_s* map, entity_s* entity_list);

/* Sleep function */
int msleep(long msec);

/* Depricated */
void draw_play_area(int X, int Y);


#endif /* SCREEN_H */