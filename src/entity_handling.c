#include "entity_handling.h"


void add_entity(entity_s* entity_list, entity_s* new_entity) {
  entity_list[new_entity_index] = *new_entity;
  new_entity_index++;
  entity_count++;
  return;
}

void move_entity(WINDOW* wnd, map_s* map, entity_s* entity, direction dir) {
  calculate_movement(map, entity, dir);
  validate_movement(map, entity);
  return;
}

void validate_movement(map_s* map, entity_s* entity) {
  switch (map->cells[entity->where_i_will_be.x][entity->where_i_will_be.y].CELL_TYPE) {
    case UNKNOWN: /* Cell type is unknown, fail program */
      perror("Riding aimlessly onward toward the UNKNOWN"); /* Credit: "Toward the Unknown" by Helstar */
      exit(-1);
      break;
    case FLOOR: /* Cell type is floor, allow movement */
      entity->where_i_was = entity->where_i_am; /* Where I am is now where I was */
      entity->where_i_am = entity->where_i_will_be; /* Where I will be is now where I am */
      break;
    case WALL: /* Cell type is wall, block movement */
      entity->where_i_will_be = entity->where_i_am; /* Where I am is still where I will be */
      break;
    case ENTITY: /* Cell type is entity, begin interaction */
      break;
  }
  return;
}

void calculate_movement(map_s* map, entity_s* entity, direction dir) {
  int SPEED = 1;

  switch(dir) {
    case LEFT:
      entity->where_i_will_be.x = entity->where_i_am.x - SPEED;
      break;
    case RIGHT:
      entity->where_i_will_be.x = entity->where_i_am.x + SPEED;
      break;
    case UP:
      entity->where_i_will_be.y = entity->where_i_am.y - SPEED;
      break;
    case DOWN:
      entity->where_i_will_be.y = entity->where_i_am.y + SPEED;
      break;
    case UPLEFT:
      entity->where_i_will_be.x = entity->where_i_am.x - SPEED;
      entity->where_i_will_be.y = entity->where_i_am.y - SPEED;
      break;
    case DOWNLEFT:
      entity->where_i_will_be.x = entity->where_i_am.x - SPEED;
      entity->where_i_will_be.y = entity->where_i_am.y + SPEED;
      break;
    case UPRIGHT:
      entity->where_i_will_be.x = entity->where_i_am.x + SPEED;
      entity->where_i_will_be.y = entity->where_i_am.y - SPEED;
      break;
    case DOWNRIGHT:
      entity->where_i_will_be.x = entity->where_i_am.x + SPEED;
      entity->where_i_will_be.y = entity->where_i_am.y + SPEED;
      break;
    case NONE:
      entity->where_i_will_be.x = entity->where_i_am.x;
      entity->where_i_will_be.y = entity->where_i_am.y;
      break;
  }

  return;
}



/* Depricated */
// void move_char(position* xy, direction dir) {
//   /* Calculate movement */
//   position xy_new;
//   xy_new.x = xy->x;
//   xy_new.y = xy->y;
//   calculate_movement(xy, &xy_new, dir);

//   /* Validate movement */
//   bool movement_is_valid = validate_movement_pos(&xy_new);

//   /* Make movement */
//   if (movement_is_valid) {
//     /* Redraw floor where we previously were */
//     move(xy->y, xy->x);
//     draw('.');
//     /* Draw where we are now */
//     move(xy_new.y, xy_new.x);
//     draw('@');
//     /* Update our position */
//     xy->x = xy_new.x;
//     xy->y = xy_new.y;
//   }

//   return;
// }
// bool validate_movement_pos(position* xy) {
//   if ((xy->x > 0 && xy->x < X && xy->y > 0 && xy->y < Y))
//     return true;
//   else
//     return false;
// }