#include <curses.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "citt.h"

/* Initialize Global */
state game_state = GET_INPUT;
int X = 0, Y = 0;
size_t new_entity_index = 0;
size_t entity_count = 0;
size_t msg_count = 0;
size_t rep_msg_count = 0;
char msg_log[MAX_LOG_LENGTH][MAX_MSG_LENGTH];


/* Define possible map names */
char* MAP00 = "src/data/map00.dat";
char* MAP01 = "src/data/map01.dat";
char* MAP02 = "src/data/map02.dat";
char* MAP03 = "src/data/map03.dat";
char* MAP04 = "src/data/map04.dat";

/* Main */
int main(void /* int argc, char** argv */) {
  WINDOW* wnd = initscr(); /* curses call to initialize window */
  cbreak(); /* curses call to set no waiting for Enter key */
  noecho(); /* curses call to set no echoing */
  clear(); /* curses call to clear screen, send cursor to position (0,0) */
  refresh(); /* curses call to implement all changes since last refresh */
  curs_set(0);
  char c;

  // /* Initialize message log */
  // for(int XL = 0; XL < MAX_MSG_LENGTH; XL++) {
  //   for(int YL = 0; YL < MAX_LOG_LENGTH; YL++) {
  //     msg_log[XL][YL] = ' ';
  //   }
  // }
  
  /* Find terminal size */
  getmaxyx(wnd, Y, X); /* curses call to find size of terminal window */

  /* Initialize game data */
  /* Map */
  char map_characters[MAX_X][MAX_Y];
  map_s map = {
    .width = 0,
    .height = 0,
  };

  /* Load map from file and set state */
  load_map_characters(MAP00, map_characters);
  convert_map_to_cells(map_characters, &map);
  game_state = CHANGING_MAP;

  /* Entities */
  entity_s entity_list[MAX_ENTITIES];
  /* Generature some entities */
  entity_s pc = {
    .what_i_am = PC,
    .what_i_look_like = {
      .CELL_TYPE = ENTITY,
      .display = '@',
      .priority = 100,
      .x = 0, .y = 0, /* UNUSED */
    },
    .where_i_was = map.cells[map.width/2][map.height/2],
    .where_i_am = map.cells[map.width/2][map.height/2],
    .where_i_will_be = map.cells[map.width/2][map.height/2],
    .what_i_am_doing = I_AM_STILL,
  };
  entity_s pc1 = {
    .what_i_am = PC,
    .what_i_look_like = {
      .CELL_TYPE = ENTITY,
      .display = 'V',
      .priority = 1,
      .x = 0, .y = 0, /* UNUSED */
    },
    .where_i_was = map.cells[map.width/3][map.height/3],
    .where_i_am = map.cells[map.width/3][map.height/3],
    .where_i_will_be = map.cells[map.width/3][map.height/3],
    .what_i_am_doing = I_AM_STILL,
  };
  entity_s pc2 = {
    .what_i_am = PC,
    .what_i_look_like = {
      .CELL_TYPE = ENTITY,
      .display = 'S',
      .priority = 1,
      .x = 0, .y = 0, /* UNUSED */
    },
    .where_i_was = map.cells[map.width/4][map.height/4],
    .where_i_am = map.cells[map.width/4][map.height/4],
    .where_i_will_be = map.cells[map.width/4][map.height/4],
    .what_i_am_doing = I_AM_STILL,
  };
  /* Add entities to entity list */
  add_entity(entity_list, &pc);
  add_entity(entity_list, &pc1);
  add_entity(entity_list, &pc2);

  /* Game loop */
  do {
    switch (game_state) {
      case ENDING:
        /* Game will end */
        break;
      case GET_INPUT:
      case PAUSED:
        /* Get input */
        c = getch();
        handle_input(wnd, &map, entity_list, &c);
        break;
      case CHANGING_MAP:
        /* Change map */
        game_state = change_map(&map, entity_list);
        break;
    }
    update_map(wnd, &map, entity_list);
  } while(game_state);

  /* Close curses */
  endwin();
  return 0;
}