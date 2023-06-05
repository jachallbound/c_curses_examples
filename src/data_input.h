#ifndef DATA_INPUT_H
#define DATA_INPUT_H

#include <curses.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "data_structures.h"
#include "screen.h"
#include "keyboard_input.h"
#include "entity_handling.h"

/* Declarations */
size_t load_map_characters(char* new_map, char map_characters[MAX_X][MAX_Y]);
int convert_map_to_cells(char map_characters[MAX_X][MAX_Y], map_s* map);
celltype decide_cell_type(char c);

size_t fsize(const char* filename, size_t dtype);

#endif /* DATA_INPUT_H */