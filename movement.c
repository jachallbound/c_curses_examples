#include <curses.h>
#include <ctype.h>
#include "data_structures.h"

/* Declarations */
WINDOW* init_curses_window();
void draw(char c);
void draw_play_area(int X, int Y);
void handle_input(position* xy, char* c);
void move_char(position* xy, direction dir);
void calculate_movement(position* xy, position* xy_new, direction dir);
bool validate_movement(position* xy);
void debug(position xy, char* msg);

/* Global */
WINDOW *wnd;
state game_state = RUNNING;
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
    handle_input(&xy, &c);
  }

  /* Close curses */
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

void handle_input(position* xy, char* c) {
  direction dir = NONE;
  game_state = RUNNING;
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
      move(xy->y, xy->x);
      break;
    case 'q': /* Quit */
      game_state = ENDING;
  }

  if (dir != NONE) {
    debug(*xy, "Moving character\n");
    move_char(xy, dir);
  }
  
  return;
}


void move_char(position* xy, direction dir) {
  /* Calculate movement */
  position xy_new;
  xy_new.x = xy->x;
  xy_new.y = xy->y;
  calculate_movement(xy, &xy_new, dir);

  /* Validate movement */
  bool movement_is_valid = validate_movement(&xy_new);

  /* Make movement */
  if (movement_is_valid) {
    /* Redraw floor where we previously were */
    move(xy->y, xy->x);
    draw('.');
    /* Draw where we are now */
    move(xy_new.y, xy_new.x);
    draw('@');
    /* Update our position */
    xy->x = xy_new.x;
    xy->y = xy_new.y;
  }

  return;
}


void calculate_movement(position* xy, position* xy_new, direction dir) {
  int SPEED = 1;

  switch(dir) {
    case LEFT:
      xy_new->x = xy->x - SPEED;
      xy_new->y = xy->y;
      break;
    case RIGHT:
      xy_new->x = xy->x + SPEED;
      xy_new->y = xy->y;
      break;
    case UP:
      xy_new->x = xy->x;
      xy_new->y = xy->y - SPEED;
      break;
    case DOWN:
      xy_new->x = xy->x;
      xy_new->y = xy->y + SPEED;
      break;
    case UPLEFT:
      xy_new->x = xy->x - SPEED;
      xy_new->y = xy->y - SPEED;
      break;
    case DOWNLEFT:
      xy_new->x = xy->x - SPEED;
      xy_new->y = xy->y + SPEED;
      break;
    case UPRIGHT:
      xy_new->x = xy->x + SPEED;
      xy_new->y = xy->y - SPEED;
      break;
    case DOWNRIGHT:
      xy_new->x = xy->x + SPEED;
      xy_new->y = xy->y + SPEED;
      break;
    case NONE:
      xy_new->x = xy->x;
      xy_new->y = xy->y;
      break;
  }

  return;
}

bool validate_movement(position* xy) {
  if ((xy->x > 0 && xy->x < X && xy->y > 0 && xy->y < Y))
    return true;
  else
    return false;
}


void debug(position xy, char* msg) {
  int buf_len = 64;
  move(Y/2, X+1);
  winsnstr(wnd, msg, buf_len);
  move(xy.y, xy.x);
  return;
}
