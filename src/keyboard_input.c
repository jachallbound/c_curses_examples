#include "keyboard_input.h"

void handle_input(WINDOW* wnd, map_s* map, entity_s* entity_list, char* c) {
  direction dir = NONE;
  game_state = GET_INPUT;
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
    case 'u': /* UPLEFT */
      dir = UPLEFT;
      break;
    case 'n': /* DOWNLEFT */
      dir = DOWNLEFT;
      break;
    case 'i': /* UPRIGHT */
      dir = UPRIGHT;
      break;
    case 'm': /* DOWNRIGHT */
      dir = DOWNRIGHT;
      break;
    case ' ': /* Select */
      display_message(wnd, map, "This is a test\n");
      break;
    case 'q': /* Quit */
      game_state = ENDING;
  }

  if (dir != NONE) {
    display_message(wnd, map, "Moving character\n");
    move_entity(wnd, map, entity_list, &entity_list[0], dir);
  }
  
  return;
}
