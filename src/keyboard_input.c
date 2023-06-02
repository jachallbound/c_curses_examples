#include "keyboard_input.h"

void handle_input(WINDOW* wnd, position* xy, char* c) {
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
    display_message(wnd, *xy, "Moving character\n");
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