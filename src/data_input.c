#include "data_input.h"

size_t load_map_characters(char* new_map, char* map_characters) {
  FILE* f;
  
  size_t map_file_length = fsize(new_map, BYTE);
  if (map_file_length > MAX_MAP_SIZE) {
    perror("Map is too large");
    return 0;
  }

  f = fopen(new_map, "r");
  if (f == NULL) {
    perror("Couldn't open map file");
    return 0;
  } else {
    fscanf(f, "%s", map_characters);
  }

  return map_file_length;
}

int convert_map_to_cells(char* map_characters, cell* map_cells, size_t map_length) {

  return 0;
}

size_t fsize(const char *filename, size_t dtype) {
  struct stat st;

  if (stat(filename, &st) == 0)
    return st.st_size/dtype;

  perror("stat() failed");
  return 0;
}