#include <curses.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "data_structures.h"
#include "data_input.h"
#include "keyboard_input.h"
#include "screen.h"

/* Global */
state game_state = RUNNING;
int X = 0, Y = 0;

/* Define possible map names */
char* MAP00 = "sr/data/map00.dat";
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
  char map_characters[MAX_MAP_SIZE];
  cell map_cells[MAX_X][MAX_Y];
  size_t map_file_length = load_map_characters(MAP00, map_characters);
  if (map_file_length == 0) {
    perror("Map was not loaded from file");
    endwin();
    return -1;
  }
  int map_conversion_status = convert_map_to_cells(map_characters, map_cells, map_file_length);
  if (map_conversion_status < 0) { 
    perror("Failed to convert map characters to cells");
    endwind();
    return -1;
  }


  /* Old, Draw play area and set cursor to 1,1 */
  draw_play_area(X, Y);

  /* Get starting cursor position */
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
      case RUNNING:
      case PAUSED:
        /* Get input */
        c = getch();
        handle_input(wnd, &xy, &c);
        break;
      case CHANGING_MAP:

        game_state = RUNNING;
        break;
    }
    
  } while(game_state);

  /* Close curses */
  endwin();
  return 0;
}