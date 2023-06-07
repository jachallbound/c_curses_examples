#include "screen.h"

void draw(char c) {
  delch();
  insch(c);
  refresh();
  return;
}

void draw_xy(char c, size_t x, size_t y) {
  move(y, x);
  draw(c);
  return;
}

void update_map(WINDOW* wnd, const map_s* map, entity_s* entity_list) {
  size_t x = 0, y = 0, e = 0;
  char c = ' ';

  for (e = 0; e < entity_count; e++) {
    if (entity_list[e].what_i_am_doing == I_AM_MOVING) {
      /* Draw floor where I was */
      x = entity_list[e].where_i_was.x;
      y = entity_list[e].where_i_was.y;
      draw_xy(map->cells[x][y].display, x, y);
      /* Draw where I am, if display priority is high enough */
      if (entity_list[e].what_i_look_like.priority > map->cells[x][y].priority) {
        x = entity_list[e].where_i_am.x;
        y = entity_list[e].where_i_am.y;
        draw_xy(entity_list[e].what_i_look_like.display, x, y);
      }
    }
  }
  return;
}

void display_message(WINDOW* wnd, const map_s* map, char* msg) {
  int buf_len = 1024;
  move(map->height/2, map->width+2);
  winsnstr(wnd, msg, buf_len);
  return;
}

state change_map(map_s* map, entity_s* entity_list) {
  /* Right now, just drop the map */
  size_t x = 0, y = 0;
  
  for (y = 0; y <= map->height; y++) {
    for (x = 0; x <= map->width; x++) {
      move(map->cells[x][y].y, map->cells[x][y].x);
      draw(map->cells[x][y].display);
    }
    msleep(50);
  }
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


/* Sleep function */
int msleep(long msec) {
  struct timespec ts;
  int res;

  if (msec < 0) {
    errno = EINVAL;
    return -1;
  }

  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);

  return res;
}