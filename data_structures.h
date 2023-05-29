#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <ctype.h>

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

typedef struct cell {
  position xy;
  bool ISWALL;
} cell;

typedef enum state {
  ENDING = 0,
  RUNNING = 1,
} state;

#endif /* DATA_STRUCTURES_H */
