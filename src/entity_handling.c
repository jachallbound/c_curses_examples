#include "entity_handling.h"

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

void add_entity(entity* entity_list, entity* new_entity, size_t index) {
  return;
}




/* Depricated */
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
bool validate_movement(position* xy) {
  if ((xy->x > 0 && xy->x < X && xy->y > 0 && xy->y < Y))
    return true;
  else
    return false;
}