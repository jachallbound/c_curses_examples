#include "keyboard_input.h"

void handle_input(WINDOW* wnd, map_s* map, position* xy, char* c) {
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
      display_message(wnd, map, *xy, "This is a test\n");
      break;
    case 'q': /* Quit */
      game_state = ENDING;
  }

  if (dir != NONE) {
    display_message(wnd, map, *xy, "Moving character\n");
    move_char(xy, dir);
  }
  
  return;
}
