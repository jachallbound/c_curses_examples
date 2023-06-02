#ifndef DATA_INPUT_H
#define DATA_INPUT_H

#include <curses.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "data_structures.h"
#include "screen.h"
#include "keyboard_input.h"

/* Declarations */
size_t load_map_characters(char* new_map, char* map_characters);
int convert_map_to_cells(char* map_characters, cell* map_cells, size_t map_length);

size_t fsize(const char* filename, size_t dtype);

#endif /* DATA_INPUT_H */