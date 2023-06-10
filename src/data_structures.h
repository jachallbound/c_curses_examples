#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <ctype.h>

#include "config.h"

/* Macros */
#define BYTE 1
#define MAX_X 128
#define MAX_Y 128
#define MAX_MAP_SIZE MAX_X*MAX_Y
#define MAX_ENTITIES 1024
#define COMPARE_XY(e0,e1) (e0.x == e1.x && e0.y == e1.y)
#define MAX_MSG_LENGTH 128
#define MAX_LOG_LENGTH 1024

/* Definitions */


/* Keyboard Input */
typedef enum direction {
  LEFT = LEFT_KEY,
  RIGHT = RIGHT_KEY,
  UP = UP_KEY,
  DOWN = DOWN_KEY,
  UPLEFT = UPLEFT_KEY,
  DOWNLEFT = DOWNLEFT_KEY,
  UPRIGHT = UPRIGHT_KEY,
  DOWNRIGHT = DOWNRIGHT_KEY,
  WAIT = WAIT_KEY,
} direction;

/* Define direction strings */
#define LEFT_STRING "west"
#define RIGHT_STRING "east"
#define UP_STRING "north"
#define DOWN_STRING "south"
#define UPLEFT_STRING "northwest"
#define DOWNLEFT_STRING "southwest"
#define UPRIGHT_STRING "northeast"
#define DOWNRIGHT_STRING "southeast"
#define WAIT_STRING "nowhere"

/* Map Cells */
typedef struct position {
  int x;
  int y;
} position;

typedef enum celltype {
  UNKNOWN = -1,
  FLOOR = 0,
  WALL = 1,
  ENTITY = 2,
} celltype;

typedef struct cell {
  size_t x;
  size_t y;
  char display;
  int priority;
  celltype CELL_TYPE;
} cell;

typedef struct map_s {
  cell cells[MAX_X][MAX_Y];
  size_t width;
  size_t height;
} map_s;


/* Entities */
typedef enum entity_action {
  I_AM_STILL,
  I_AM_MOVING,
  I_AM_INTERACTING,
} entity_action;

typedef enum entity_type {
  PC, /* Player Character */
  NPC, /* Non-Player Character */
} entity_type;

typedef enum visibility {
  VISIBLE = 0,
  INVISIBLE = 1,
  SHROUDED = 2,
} visibility;

typedef struct entity_s {
  entity_type what_i_am;
  cell what_i_look_like;
  cell where_i_was;
  cell where_i_am;
  cell where_i_will_be;
  entity_action what_i_am_doing;
} entity_s;


/* Game State */
typedef enum state {
  ENDING = 0,
  GET_INPUT = 1,
  CHANGING_MAP = 2,
  PAUSED = 3,
} state;

/* Global */
extern int X, Y;
extern state game_state;
extern size_t new_entity_index, entity_count;
extern char msg_log[MAX_LOG_LENGTH][MAX_MSG_LENGTH];
extern size_t msg_count;
extern size_t rep_msg_count;

#endif /* DATA_STRUCTURES_H */
