#include <curses.h>
#include <ctype.h>
#include "data_structures.h"

/* Declarations */
void draw(char c);
void draw_play_area(int X, int Y);
void handle_input(int* x, int* y, char* c);
WINDOW* init_curses_window();

/* Global */
WINDOW *wnd;
int X = 0, Y = 0;

/* Main */
int main(int argc, char** argv) {
  wnd = init_curses_window();
  int term_X = 0, term_Y = 0;
  char c;
  
  /* Choose play area size */
  X = 21;
  Y = 21;
  getmaxyx(wnd, term_X, term_Y); /* curses call to find size of terminal window */
  X = (term_X < X ? term_X : X); /* Reduce X,Y to terminal size if too large */
  Y = (term_Y < Y ? term_Y : Y);

  draw_play_area(X, Y);
  int x = getcurx(wnd);
  int y = getcury(wnd);

  while(1) {
    c = getch();
    if (c == 'q') break;
    handle_input(&x, &y, &c);
  }
  endwin();
  return 0;
}

/* Definitions */
WINDOW* init_curses_window() {
  WINDOW* wnd = initscr(); /* curses call to initialize window */
  cbreak(); /* curses call to set no waiting for Enter key */
  noecho(); /* curses call to set no echoing */
  clear(); /* curses call to clear screen, send cursor to position (0,0) */
  refresh(); /* curses call to implement all changes since last refresh */
  
  return wnd;
}

void draw(char c) {
  delch();
  insch(c);
  refresh();

  return;
}

void draw_play_area(int X, int Y) {
  int x = 0, y = 0;
  char c;
  /* Draw walls of play area */
  move(0, 0);
  for (y = 0; y <= Y; y++) {
    if (y == 0 || y == Y) {
      c = '=';
      for (x = 0; x <= X; x++) {
        move(y, x);
        draw(c);
      }
    }
    else {
      c = '|';
      x = 0;
      move(y, x);
      draw(c);
      
      x = X;
      move(y, x);
      draw(c);
    }
  }
  /* Reset position within walls we just drew */
  move(1, 1);

  return;
}

void handle_input(int* x, int* y, char* c) {
  int x_new = *x;
  int y_new = *y;
  direction dir = NONE;
  switch(*c) {
    case 'h': /* LEFT */
      dir = LEFT;
      break;
    case 'l': /* RIGHT */
      dir = RIGHT;
      break;
    case 'k': /* UP */
      dir = UP;
      break;
    case 'j': /* DOWN */
      dir = DOWN;
      break;
    case 'y': /* UPLEFT */
      dir = UPLEFT;
      break;
    case 'b': /* DOWNLEFT */
      dir = DOWNLEFT;
      break;
    case 'u': /* UPRIGHT */
      dir = UPRIGHT;
      break;
    case 'n': /* DOWNRIGHT */
      dir = DOWNRIGHT;
      break;
    case ' ': /* Select */
      move(Y/2, X+1);
      winsnstr(wnd, "This is a test\n", 32);
      move(*y, *x);
  }


  move(*y, *x);
  delch();
  insch(*c);
  return;
}