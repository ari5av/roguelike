#include <stdlib.h>
#include "init.h"
#include "map_window.h"
#include "game.h"
#include "command.h"

void handle_end_signal(int signum)
{
  endwin();
  printf("received signal %d\n", signum);
  exit(EXIT_SUCCESS);
}

void handle_keypress_normal(int key_input)
{
  switch (key_input)
  {
    case 'h':
      if (is_walkable(y, x-1)) {
        x--;
        needs_refresh = TRUE;
      }
      break;
    case 'j':
      if (is_walkable(y+1, x)) {
        y++;
        needs_refresh = TRUE;
      }
      break;
    case 'k':
      if (is_walkable(y-1, x)) {
        y--;
        needs_refresh = TRUE;
      }
      break;
    case 'l':
      if (is_walkable(y, x+1)) {
        x++;
        needs_refresh = TRUE;
      }
      break;
    case 'y':
      if (is_walkable(y-1, x-1)) {
        x--;
        y--;
        needs_refresh = TRUE;
      }
      break;
    case 'u':
      if (is_walkable(y-1, x+1)) {
        x++;
        y--;
        needs_refresh = TRUE;
      }
      break;
    case 'b':
      if (is_walkable(y+1, x-1)) {
        x--;
        y++;
        needs_refresh = TRUE;
      }
      break;
    case 'n':
      if (is_walkable(y+1, x+1)) {
        x++;
        y++;
        needs_refresh = TRUE;
      }
      break;
    case '#':
      // enter command mode!
      enter_command_mode();
      break;
    default:
      break;
  }
}

void handle_keypress_command(int key_input)
{
  switch (key_input)
  {
    case 8:
    case 127:
      // ctrl-H or backspace character
      backspace_command();
      break;
    case 10:
    case 13:
      // execute the command if possible
      execute_command();
      // exit command mode
      exit_command_mode();
      break;
    case 27:
      // escape key cancels
      exit_command_mode();
    default:
      // if user has typed a displayable character as part of the command
      if (key_input >= ' ' && key_input <= '~') {
        add_char_to_command(key_input);
      }
      break;
  }
}

void handle_keypress_waiting(int key_input) {}

void handle_keypress_selecting(int key_input) {}

// this function runs the game
// GameMode is a global state machine
// it tells game_tick whether to receive input, and what to do with it
void game_tick()
{
  char key_input;
  char c;
  // what's my current mode?
  // MODE_NORMAL -> this is the regular game mode
  // MODE_COMMAND -> user is in command mode
  // MODE_WAITING -> waiting for a "press any key to continue"
  // MODE_SELECTING -> user is selecting something from a menu
  // MODE_ANIMATION -> something is currently animating on the screen and we can't deal with input

  // if I need to grab a keypress, do it here
  // reminder: getch() is non-blocking!
  // reminder: often a keypress is intended to change GameMode!
  switch(GameMode) {
    case MODE_NORMAL:
      key_input = getch();
      while ((c = getch()) != ERR);
      handle_keypress_normal(key_input);
      break;
    case MODE_COMMAND:
      key_input = getch();
      handle_keypress_command(key_input);
      break;
    case MODE_WAITING:
      key_input = getch();
      handle_keypress_waiting(key_input);
      break;
    case MODE_SELECTING:
      key_input = getch();
      handle_keypress_selecting(key_input);
      break;
    case MODE_ANIMATION:
      // do not get a keypress
      // continue my current animation...
      break;
    default:
      // should never get here
      break;
  }
}
