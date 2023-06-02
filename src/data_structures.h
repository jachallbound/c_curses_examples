#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <ctype.h>

/* Macros */
#define BYTE 1
#define MAX_X 128
#define MAX_Y 128
#define MAX_MAP_SIZE MAX_X*MAX_Y

/* Definitions */
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

typedef struct position {
  int x;
  int y;
} position;

typedef enum celltype {
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

typedef enum state {
  ENDING = 0,
  RUNNING = 1,
  CHANGING_MAP = 2,
  PAUSED = 3,
} state;


#endif /* DATA_STRUCTURES_H */
