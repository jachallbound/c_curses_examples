#include "keyboard_input.h"

void handle_input(WINDOW* wnd, position* xy, char* c) {
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
