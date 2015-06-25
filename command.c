#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include "init.h"
#include "game.h"
#include "command.h"
#include "input_window.h"
#include <stdio.h>

FILE * my_log;

void enter_command_mode()
{
  my_log = fopen("log.txt", "w+");
  fprintf(my_log, "entered command mode\n");
  fflush(my_log);

  // set the game mode to command
  GameMode = MODE_COMMAND;

  // clear the command buffer
  memset(command_buffer, 0, MAX_COMMAND_LEN);

  // the command now has zero bytes
  command_size = 0;

  // clear the input window
  wclear(win_input);

  // write a # character
  set_cell_on_input(1, 2, '#');

  // show the cursor and place it next to the #
  curs_set(1);
  /*
  if (ERR == wmove(stdscr, 26, command_size+3)) {
    fprintf(my_log, "couldn't move!\n");
    fflush(my_log);
  } else {
    fprintf(my_log, "moved!\n");
    fflush(my_log);
  }
  */

  move(26, command_size+3);

  // we updated the screen
  wrefresh(win_input);
  needs_refresh = TRUE;
}

void add_char_to_command(int key_input)
{
  // if it's too big, automatically exit command mode and do not execute
  if (command_size == MAX_COMMAND_LEN) {
    exit_command_mode();
    return;
  }

  int x, y;
  getyx(stdscr, y, x);
  fprintf(my_log, "%c %d %d\n", (char)key_input, y, x);
  fflush(my_log);

  // add the character to the end of the command buffer
  command_buffer[command_size] = (char)key_input;

  // display the character
  set_cell_on_input(1, command_size+3, (char)key_input);

  // move the cursor to the right
  //wmove(win_input, 1, command_size+4);
  move(26, command_size+4);

  // increase the size of the current command
  command_size += 1;

  // we updated the screen
  refresh();
  needs_refresh = TRUE;
}

void backspace_command()
{
  // can't backspace into the negative
  if (command_size == 0) {
    exit_command_mode();
    return;
  }

  int x, y;
  getyx(stdscr, y, x);
  fprintf(my_log, "^H %d %d\n", y, x);
  fflush(my_log);

  // drop the last typed character
  command_buffer[command_size] = '\0';

  // erase it from the window
  set_cell_on_input(1, command_size+2, '\0');

  // move the cursor left one space
  //wmove(win_input, 1, command_size+2);
  move(26, command_size+2);

  // the strlen of the command has now dropped by one
  command_size -= 1;

  // we updated the screen
  refresh();
  needs_refresh = TRUE;
}

void execute_command()
{
  // if the command exists, handle appropriately
  if (!strcasecmp(command_buffer, "quit") ||
      !strcasecmp(command_buffer, "exit"))
  {
    should_quit = TRUE;
  }
  // otherwise, do nothing
}

void exit_command_mode()
{
  int x, y;
  getyx(stdscr, y, x);
  fprintf(my_log, "exit %d %d\n", y, x);
  fflush(my_log);
  fclose(my_log);
  
  // set the game mode back to normal
  GameMode = MODE_NORMAL;

  // clear the command buffer
  memset(command_buffer, 0, MAX_COMMAND_LEN);

  // clear the input window
  for (int i=0;i<360;i++) {
    Input[i] = ' ';
  }

  // hide the cursor
  curs_set(0);

  // we updated the screen
  refresh();
  needs_refresh = TRUE;
}
