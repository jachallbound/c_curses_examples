#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <ctype.h>

/* Macros */
#define BYTE 1
#define MAX_X 128
#define MAX_Y 128
#define MAX_MAP_SIZE MAX_X*MAX_Y

/* Definitions */

/* Keyboard Input */
typedef enum direction {
  LEFT = 'h',
  RIGHT = 'l',
  UP = 'k',
  DOWN = 'j',
  UPLEFT = 'y',
  DOWNLEFT = 'b',
  UPRIGHT = 'u',
  DOWNRIGHT = 'n',
  NONE = '.',
} direction;

/* Map Cells */
typedef struct position {
  int x;
  int y;
} position;

typedef enum celltype {
  UNKNOWN = -1,
  FLOOR = 0,
  WALL = 1,
  PED = 2,
  PC = 3,
} celltype;

typedef struct cell {
  position xy;
  char display;
  int priority;
  celltype CELL_TYPE;
} cell;

typedef struct map_s {
  cell cells[MAX_X][MAX_Y];
  size_t width;
  size_t height;
} map_s;

/* Game State */
typedef enum state {
  ENDING = 0,
  GET_INPUT = 1,
  CHANGING_MAP = 2,
  PAUSED = 3,
} state;


#endif /* DATA_STRUCTURES_H */
