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
void draw_xy(char c, size_t x, size_t y);
void update_map(WINDOW* wnd, const map_s* map, entity_s* entity_list);
void display_message(WINDOW* wnd, const map_s* map, char* msg);
state change_map(map_s* map, entity_s* entity_list);

/* Sleep function */
int msleep(long msec);

#endif /* SCREEN_H */