#include "keyboard_input.h"

void handle_input(WINDOW* wnd, map_s* map, entity_s* entity_list, char* c) {
  direction dir = NONE;
  game_state = GET_INPUT;
  switch(*c) {
    case LEFT_KEY: /* LEFT */
      dir = LEFT;
      break;
    case RIGHT_KEY: /* RIGHT */
      dir = RIGHT;
      break;
    case UP_KEY: /* UP */
      dir = UP;
      break;
    case DOWN_KEY: /* DOWN */
      dir = DOWN;
      break;
    case UPLEFT_KEY: /* UPLEFT */
      dir = UPLEFT;
      break;
    case DOWNLEFT_KEY: /* DOWNLEFT */
      dir = DOWNLEFT;
      break;
    case UPRIGHT_KEY: /* UPRIGHT */
      dir = UPRIGHT;
      break;
    case DOWNRIGHT_KEY: /* DOWNRIGHT */
      dir = DOWNRIGHT;
      break;
    case WAIT_KEY: /* DOWNRIGHT */
      dir = WAIT;
      break;
    case SELECT_KEY: /* Select */
      display_message(wnd, map, "This is a test\n");
      break;
    case QUIT_KEY: /* Quit */
      game_state = ENDING;
  }

  if (dir != NONE) {
    move_entity(wnd, map, entity_list, &entity_list[0], dir);
  }
  
  return;
}
