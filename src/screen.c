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
  int buf_len = 1024;
  move(Y/2, X+1);
  winsnstr(wnd, msg, buf_len);
  move(xy.y, xy.x);
  return;
}

state change_map(map_s* map, position* cur_pos) {
  /* Right now, just drop the map */
  size_t x = 0, y = 0;
  for (y = 0; y <= map->height; y++) {
    for (x = 0; x <= map->width; x++) {
      move(map->cells[x][y].xy.y,map->cells[x][y].xy.x);
      draw(map->cells[x][y].display);
    }
  }
  move(cur_pos->y, cur_pos->x);
  return GET_INPUT;
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