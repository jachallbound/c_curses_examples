#ifndef ENTITY_HANDLING_H
#define ENTITY_HANDLING_H

#include <curses.h>
#include <ctype.h>
#include <string.h>

#include "data_structures.h"
#include "screen.h"

void add_entity(entity_s* entity_list, entity_s* new_entity);

void move_entity(WINDOW* wnd, map_s* map, entity_s* entity_list, entity_s* entity, direction dir);
void calculate_movement(WINDOW* wnd, map_s* map, entity_s* entity_list, entity_s* entity, direction dir);
void validate_movement(WINDOW* wnd, map_s* map, entity_s* entity_list, entity_s* entity, direction dir);
void report_movement(WINDOW* wnd, map_s* map, entity_s* entity, direction dir);

void entity_interaction(WINDOW* wnd, map_s* map, entity_s* entity_1, entity_s* entity_2);

#endif /* ENTITY_HANDLING_H */