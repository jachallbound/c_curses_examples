#ifndef ENTITY_HANDLING_H
#define ENTITY_HANDLING_H


#include <curses.h>
#include <ctype.h>

#include "data_structures.h"
#include "screen.h"

void calculate_movement(position* xy, position* xy_new, direction dir);


/* Depricated */
void move_char(position* xy, direction dir);
bool validate_movement(position* xy);

#endif /* ENTITY_HANDLING_H */