#include <curses.h>
#include <ctype.h>
#include "data_structures.h"

/* Declarations */
void draw(char c);
void draw_play_area(int X, int Y);
void handle_input(int* x, int* y, char* c);
void move_char(int* x, int* y, direction dir);
void calculate_movement(int* x, int* y, int* x_new, int* y_new, direction dir);
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
  return;
}

void draw_play_area(int X, int Y) {
  int x = 0, y = 0;
  char c;
  /* Draw walls of play area */
  move(0, 0);
  for (y = 0; y <= Y; y++) {
    for (x = 0; x <= X; x++) {
      if (y == 0 || y == Y) {
        c = '=';
      }
      else if (x == 0 || x == X) {
        c = '|';
      }
      else {
        c = '.';
      }
      move(y, x);
      draw(c);
    }
  }
  /* Reset position within walls we just drew */
  move(1, 1);

  return;
}

void handle_input(int* x, int* y, char* c) {
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

  if (dir != NONE) move_char(x, y, dir);

  /*
  move(*y, *x);
  delch();
  insch(*c);
  */

  return;
}


void move_char(int* x, int* y, direction dir) {
  /* Calculate movement */
  int* x_new;
  int* y_new;
  calculate_movement(x, y, x_new, y_new, dir);

  bool movement_is_valid = true;
  /* TODO: Decide if movement is valid */

  /* Make movement */
  if (movement_is_valid) {
    move(*y, *x);
    draw('.');
    move(*y_new, *x_new);
    draw('@');

    *x = *x_new;
    *y = *y_new;
  }

  return;
}


void calculate_movement(int* x, int* y, int* x_new, int* y_new, direction dir) {
  *x_new = *x;
  *y_new = *y;
  int SPEED = 1;

  switch(dir) {
    case LEFT:
      *x_new = *x - SPEED;
      *y_new = *y;
      break;
    case RIGHT:
      *x_new = *x + SPEED;
      *y_new = *y;
      break;
    case UP:
      *x_new = *x;
      *y_new = *y - SPEED;
      break;
    case DOWN:
      *x_new = *x;
      *y_new = *y + SPEED;
      break;
    case UPLEFT:
      *x_new = *x - SPEED;
      *y_new = *y - SPEED;
      break;
    case DOWNLEFT:
      *x_new = *x - SPEED;
      *y_new = *y + SPEED;
      break;
    case UPRIGHT:
      *x_new = *x + SPEED;
      *y_new = *y - SPEED;
      break;
    case DOWNRIGHT:
      *x_new = *x + SPEED;
      *y_new = *y + SPEED;
      break;
  }

  return;
}
