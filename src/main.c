#include <curses.h>
#include <ctype.h>
#include "data_structures.h"
#include "movement.h"

/* Global */
state game_state = RUNNING;
int X = 0, Y = 0;

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

  /* Draw play area and set cursor to 1,1 */
  draw_play_area(X, Y);
  int x = getcurx(wnd);
  int y = getcury(wnd);
  position xy;
  xy.x = x;
  xy.y = y;

  /* Game loop */
  while(game_state) {
    /* Get input */
    c = getch();
    handle_input(wnd, &xy, &c);
  }

  /* Close curses */
  endwin();
  return 0;
}