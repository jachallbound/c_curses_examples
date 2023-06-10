#include "screen.h"

/* Map functions */
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

void update_entity_positions(WINDOW* wnd, const map_s* map, entity_s* entity_list) {
  size_t x = 0, y = 0, e = 0;
  for (e = 0; e < entity_count; e++) {
    /* Draw where I am, if display priority is high enough */
    x = entity_list[e].where_i_am.x;
    y = entity_list[e].where_i_am.y;
    if (entity_list[e].what_i_look_like.priority > map->cells[x][y].priority) {
      draw_xy(entity_list[e].what_i_look_like.display, x, y);
    }
    switch (entity_list[e].what_i_am_doing) {
      case I_AM_MOVING:
        /* If I am moving, then draw map cell where I was */
        x = entity_list[e].where_i_was.x;
        y = entity_list[e].where_i_was.y;
        draw_xy(map->cells[x][y].display, x, y);
      case I_AM_WAITING:
        report_movement(wnd, map, &entity_list[e]);
        break;
      default:
        break;
    }
  }
  return;
}

state draw_map(map_s* map) { /* , entity_s* entity_list */
  /* Right now, just draw the map */
  size_t x = 0, y = 0;
  
  for (y = 0; y <= map->height; y++) {
    for (x = 0; x <= map->width; x++) {
      draw_xy(map->cells[x][y].display, map->cells[x][y].x, map->cells[x][y].y);
    }
    msleep(50);
  }
  return GET_INPUT;
}

/* Message functions */
void display_message(WINDOW* wnd, const map_s* map, char* msg) {
  /* Save message to log file */
  FILE* userlogfile = fopen(USER_LOG_FILE, "a");
  fprintf(userlogfile, "%s", msg);
  fclose(userlogfile);
  /* Put new message into log */
  strncpy(msg_log[msg_count++], msg, MAX_MSG_LENGTH);
  if (msg_count >= MAX_LOG_LENGTH) msg_count = 0;
  /* Display log */
  size_t m = 0, m_max = 0;
  m_max = (msg_count > (size_t)Y ? (size_t)Y : msg_count);
  for(m = 0; m < m_max; m++) {
    move(Y-m-1, map->width+2);
    winsnstr(wnd, msg_log[msg_count-m-1], MAX_MSG_LENGTH);
  }
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