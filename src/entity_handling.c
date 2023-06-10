#include "entity_handling.h"


void add_entity(entity_s* entity_list, entity_s* new_entity) {
  entity_list[new_entity_index] = *new_entity;
  new_entity_index++;
  entity_count++;
  return;
}

void entity_interaction(WINDOW* wnd, map_s* map, entity_s* entity_0, entity_s* entity_1) {
  char msg[MAX_MSG_LENGTH];
  char c0[2]; c0[0] = entity_0->what_i_look_like.display; c0[1] = '\0'; /* I hate C strings */
  char c1[2]; c1[0] = entity_1->what_i_look_like.display; c1[1] = '\0';
  char interact_str[] = " interacts with ";
  strcpy(msg, c0);
  strcat(msg, interact_str);
  strcat(msg, c1);
  strcat(msg, "\n");
  display_message(wnd, map, msg);
  return;
}

void move_entity(WINDOW* wnd, map_s* map, entity_s* entity_list, entity_s* entity, direction dir) {
  calculate_movement(wnd, map, entity_list, entity, dir);
  validate_movement(wnd, map, entity_list, entity, dir);
  return;
}

void validate_movement(WINDOW* wnd, map_s* map, entity_s* entity_list, entity_s* entity, direction dir) {
  size_t e = 0;
  for (e = 0; e < entity_count; e++) {
    if (COMPARE_XY(entity_list[e].where_i_am, entity->where_i_will_be)) { //(entity_list[e].where_i_am.x == entity->where_i_will_be.x && entity_list[e].where_i_am.y == entity->where_i_will_be.y) {
      entity->where_i_will_be = entity->where_i_am;
      entity->what_i_am_doing = I_AM_INTERACTING;
      entity_interaction(wnd, map, entity, &entity_list[e]);
      return; /* We are interacting, so don't check cell movement */
              /* Returning here disallows multiple interactions, possibly change this */
    }
  }
  switch (map->cells[entity->where_i_will_be.x][entity->where_i_will_be.y].CELL_TYPE) {
    case UNKNOWN: /* Cell type is unknown, fail program */
      perror("Riding aimlessly onward toward the UNKNOWN"); /* Credit: "Toward the Unknown" by Helstar */
      exit(-1);
      break;
    case FLOOR: /* Cell type is floor, allow movement */
      entity->where_i_was = entity->where_i_am; /* Where I am is now where I was */
      entity->where_i_am = entity->where_i_will_be; /* Where I will be is now where I am */
      entity->what_i_am_doing = I_AM_MOVING;
      report_movement(wnd, map, entity, dir);
      break;
    case WALL: /* Cell type is wall, block movement */
      entity->where_i_will_be = entity->where_i_am; /* Where I am is still where I will be */
      entity->what_i_am_doing = I_AM_STILL;
      break;
    case ENTITY: /* We should not reach this, and map cells probably wont be se to ENTITY */
      entity->where_i_will_be = entity->where_i_am;
      entity->what_i_am_doing = I_AM_INTERACTING;
      break;
  }
  return;
}

void report_movement(WINDOW* wnd, map_s* map, entity_s* entity, direction dir) {
  char msg[MAX_MSG_LENGTH];
  char c0[2]; c0[0] = entity->what_i_look_like.display; c0[1] = '\0'; /* I hate C strings */
  strcpy(msg, c0);
  strcat(msg, " moved ");
  switch (dir) {
    case LEFT:
      strcat(msg, LEFT_STRING);
      break;
    case RIGHT:
      strcat(msg, RIGHT_STRING);
      break;
    case UP:
      strcat(msg, UP_STRING);
      break;
    case DOWN:
      strcat(msg, DOWN_STRING);
      break;
    case UPLEFT:
      strcat(msg, UPLEFT_STRING);
      break;
    case DOWNLEFT:
      strcat(msg, DOWNLEFT_STRING);
      break;
    case UPRIGHT:
      strcat(msg, UPRIGHT_STRING);
      break;
    case DOWNRIGHT:
      strcat(msg, DOWNRIGHT_STRING);
      break;
    case WAIT:
      strcat(msg, WAIT_STRING);
      break;
  }
  strcat(msg, "\n");
  display_message(wnd, map, msg);
  return;
}

void calculate_movement(WINDOW* wnd, map_s* map, entity_s* entity_list, entity_s* entity, direction dir) {
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
  }

  return;
}