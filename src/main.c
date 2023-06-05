#include <curses.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "citt.h"

/* Initialize Global */
state game_state = GET_INPUT;
int X = 0, Y = 0;
size_t n_entities = 0;

/* Define possible map names */
/* I don't like this, but I dislike C strings even more */
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

  int term_X = 0, term_Y = 0;
  char c;
  
  /* Choose play area size */
  X = 21;
  Y = 21;
  getmaxyx(wnd, term_X, term_Y); /* curses call to find size of terminal window */
  X = (term_X < X ? term_X : X); /* Reduce X,Y to terminal size if too large */
  Y = (term_Y < Y ? term_Y : Y);

  /* Initialize game data */
  /* Map */
  char map_characters[MAX_X][MAX_Y];
  map_s map = {
    .width = 0,
    .height = 0,
  };
  /* Entities */
  entity entity_list[MAX_ENTITIES];

  /* Load map from file and set state */
  load_map_characters(MAP00, map_characters);
  convert_map_to_cells(map_characters, &map);
  game_state = CHANGING_MAP;

  entity pc = {
    .what_i_am = PC,
    .what_i_look_like = {
      .CELL_TYPE = ENTITY,
      .display = '@',
      .priority = 100,
      .xy = {
        .x = 1,
        .y = 1,
      },
    },
    .where_i_was = map.cells[1][1],
    .where_i_am = map.cells[1][1],
    .what_i_am_doing = I_AM_STILL,
  };
  add_entity(entity_list, &pc, 0);

  /* Get starting cursor position */
  move(10, 10);
  int x = getcurx(wnd);
  int y = getcury(wnd);
  position xy;
  xy.x = x;
  xy.y = y;

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
        handle_input(wnd, &map, &xy, &c);
        break;
      case CHANGING_MAP:
        /* Change map */
        game_state = change_map(&map, &xy);
        break;
    }
    
  } while(game_state);

  /* Close curses */
  endwin();
  return 0;
}











  /* Old, Draw play area and set cursor to 1,1 */
  // draw_play_area(X, Y);