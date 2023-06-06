#include "data_input.h"

size_t load_map_characters(char* new_map, char map_characters[MAX_X][MAX_Y]) {
  FILE* f;
  size_t m = 0, x = 0, y = 0;
  char c = 0;
  
  size_t map_len = fsize(new_map, BYTE);

  if (map_len > MAX_MAP_SIZE) {
    perror("Map is too large");
    sleep(3);
    endwin();
    exit(-1);
  }

  f = fopen(new_map, "r");
  if (f == NULL) {
    perror("Couldn't open map file");
    sleep(3);
    endwin();
    exit(-1);
  } else {
    x = 0;
    y = 0;
    for (m = 0; m < map_len; m++) {
      fscanf(f, "%c", &c);
      map_characters[x][y] = c;
      x++;
      if (c == '\n') {
        x = 0;
        y++;
      }
    }
  }
  fclose(f);
  return map_len;
}

int convert_map_to_cells(char map_characters[MAX_X][MAX_Y], map_s* map) {
  size_t x = 0, y = 0;

  for (y = 0; y < MAX_Y; y++) {
    for (x = 0; x < MAX_X; x++) {
      switch (map_characters[x][y]) {
        case '\n':
          map->width = (x > map->width) ? x : map->width;
          map->height++;
          break;
        default:
          map->cells[x][y].x = x;
          map->cells[x][y].y = y;
          map->cells[x][y].display = map_characters[x][y];
          map->cells[x][y].priority = 0;
          map->cells[x][y].CELL_TYPE = decide_cell_type(map_characters[x][y]);
          break;
      }
      if (map_characters[x][y] == '\0') break;
    }
    if (map_characters[0][y] == '\0') break;
  }
  map->width--;
  
  return 0;
}

celltype decide_cell_type(char c) {
  switch (c) {
    case '.':
    case ' ':
      return FLOOR;
      break;
    case '|':
    case '=':
      return WALL;
      break;
    default:
      return UNKNOWN;
      break;
  }
  return UNKNOWN;
}

size_t fsize(const char *filename, size_t dtype) {
  struct stat st;

  if (stat(filename, &st) == 0)
    return st.st_size/dtype;

  perror("stat() failed");
  return 0;
}