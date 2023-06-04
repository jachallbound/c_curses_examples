#include <curses.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "data_structures.h"
#include "data_input.h"
#include "keyboard_input.h"
#include "screen.h"

/* Global */
state game_state = GET_INPUT;
int X = 0, Y = 0;

/* Define possible map names */
/* I don't like this, but I dislike C strings even more */
char* MAP00 = "src/data/map00.dat";
char* MAP01 = "src/data/map01.dat";
char* MAP02 = "src/data/map02.dat";
char* MAP03 = "src/data/map03.dat";
char* MAP04 = "src/data/map04.dat";

/* Main */
int main(int argc, char** argv) {
  WINDOW* wnd = initscr(); /* curses call to initialize window */
  cbreak(); /* curses call to set no waiting for Enter key */
  noecho(); /* curses call to set no echoing */
  clear(); /* curses call to clear screen, send cursor to position (0,0) */
  refresh(); /* curses call to implement all changes since last refresh */

  int term_X = 0, term_Y = 0;
  char c;
  
  /* Choose play area size */
  X = 21;
  Y = 21;
  getmaxyx(wnd, term_X, term_Y); /* curses call to find size of terminal window */
  X = (term_X < X ? term_X : X); /* Reduce X,Y to terminal size if too large */
  Y = (term_Y < Y ? term_Y : Y);

  /* Load map from file and set state */
  char map_characters[MAX_X][MAX_Y];
  map_s map = {
    .width = 0,
    .height = 0,
  };
  size_t map_len = load_map_characters(MAP00, map_characters);
  convert_map_to_cells(map_characters, &map, map_len);
  game_state = CHANGING_MAP;

  /* Old, Draw play area and set cursor to 1,1 */
  // draw_play_area(X, Y);

  /* Get starting cursor position */
  move(1, 1);
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
        handle_input(wnd, &xy, &c);
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