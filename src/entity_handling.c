#include "entity_handling.h"

void add_entity(entity_s* entity_list, entity_s* new_entity) {
  entity_list[new_entity_index] = *new_entity;
  new_entity_index++;
  entity_count++;
  return;
}

void entity_interaction(WINDOW* wnd, map_s* map, entity_s* entity_0, entity_s* entity_1) {
  char msg[MAX_MSG_LENGTH];
  char interact_str[20];
  /* Grammar */
  if (entity_0->what_i_am == PC) {
    strcpy(interact_str, " interact with ");
  } else {
    strcpy(interact_str, " interacts with ");
  }
  /* Build interaction message */
  strcpy(msg, entity_0->who_i_am.name);
  strcat(msg, interact_str);
  strcat(msg, entity_1->who_i_am.name);
  strcat(msg, "\n");
  display_message(wnd, map, msg);
  return;
}

void report_movement(WINDOW* wnd, const map_s* map, entity_s* entity) {
  int dx = 0, dy = 0;
  char msg[MAX_MSG_LENGTH];
  char movement_str[20];
  /* Grammar */
  if (entity->what_i_am == PC) {
    strcpy(movement_str, " move ");
  } else {
    strcpy(movement_str, " moves ");
  }
   /* Build movement message */
  strcpy(msg, entity->who_i_am.name);
  strcat(msg, " moved ");
  /* Decide direction of movement */
  dy = entity->where_i_am.y - entity->where_i_was.y;
  dx = entity->where_i_am.x - entity->where_i_was.x;
  /* North or south */
  if (dy > 0) strcat(msg, "south ");
  else if (dy < 0) strcat(msg, "north ");
  /* East or west */
  if (dx > 0) strcat(msg, "east ");
  else if (dx < 0) strcat(msg, "west ");
  /* Didn't move at all */
  if (dx == 0 && dy == 0) strcat(msg, "nowhere");
  /* End message */
  strcat(msg, "\n");
  display_message(wnd, map, msg);
  return;
}

void move_entity(WINDOW* wnd, map_s* map, entity_s* entity_list, entity_s* entity, direction dir) {
  calculate_movement(entity, dir);
  validate_movement(wnd, map, entity_list, entity, dir);
  return;
}

void validate_movement(WINDOW* wnd, map_s* map, entity_s* entity_list, entity_s* entity, direction dir) {
  size_t e = 0;
  /* Handle entity interaction */
  if (dir != WAIT) { /* WAITing will interact with self */
    for (e = 0; e < entity_count; e++) {
      if (COMPARE_XY(entity_list[e].where_i_am, entity->where_i_will_be)) { //(entity_list[e].where_i_am.x == entity->where_i_will_be.x && entity_list[e].where_i_am.y == entity->where_i_will_be.y) {
        entity->where_i_will_be = entity->where_i_am;
        entity->what_i_am_doing = I_AM_INTERACTING;
        entity_interaction(wnd, map, entity, &entity_list[e]);
        return; /* We are interacting, so don't check cell movement */
                /* Returning here disallows multiple interactions, possibly change this */
      }
    }
  }
  /* Handle movement */
  switch (map->cells[entity->where_i_will_be.x][entity->where_i_will_be.y].CELL_TYPE) {
    case UNKNOWN: /* Cell type is unknown, fail program */
      perror("Riding aimlessly onward toward the UNKNOWN"); /* Credit: "Toward the Unknown" by Helstar */
      exit(-1);
      break;
    case FLOOR: /* Cell type is floor, allow movement */
      entity->where_i_was = entity->where_i_am; /* Where I am is now where I was */
      entity->where_i_am = entity->where_i_will_be; /* Where I will be is now where I am */
      entity->what_i_am_doing = (dir == WAIT ? I_AM_WAITING : I_AM_MOVING);
      
      break;
    case WALL: /* Cell type is wall, block movement */
      entity->where_i_will_be = entity->where_i_am; /* Where I am is still where I will be */
      entity->what_i_am_doing = I_AM_STILL;
      break;
    case ENTITY: /* We will probably not reach here */
      entity->where_i_will_be = entity->where_i_am;
      entity->what_i_am_doing = I_AM_STILL;
      break;
  }
  return;
}

void calculate_movement(entity_s* entity, direction dir) { /* WINDOW* wnd, map_s* map, entity_s* entity_list,  */
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
    case WAIT:
      entity->where_i_will_be.x = entity->where_i_am.x;
      entity->where_i_will_be.y = entity->where_i_am.y;
      break;
    default:
      break;
  }

  return;
}