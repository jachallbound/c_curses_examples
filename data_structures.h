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

typedef struct cell {
  int x;
  int y;
  bool ISWALL;
} cell;

#endif /* DATA_STRUCTURES_H */