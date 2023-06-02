#include "screen.h"

void draw(char c) {
  delch();
  insch(c);
  return;
}

void draw_at_position(char c, position xyz) {

  return;
}

void display_message(WINDOW* wnd, position xy, char* msg) {
  int buf_len = 64;
  move(Y/2, X+1);
  winsnstr(wnd, msg, buf_len);
  move(xy.y, xy.x);
  return;
}

int draw_map(cell* map_cells, size_t map_length) {

  return 0;
}

/* Depricated */
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