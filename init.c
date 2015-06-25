#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "init.h"
#include "game.h"

// this is a temporary function
// it ain't stickin' around
void init_map()
{
  Map = (void *)malloc(2250);
  for (int i=0;i<2250;i++) {
    Map[i] = '.';
  }
}

void init_windows()
{
  win_inventory = newwin(25, 29, 0, 0);
  win_map       = newwin(25, 90, 0, 30);
  win_input     = newwin(3, 120, 25, 0);
  win_status    = newwin(7, 120, 28, 0);

  pan_inventory = new_panel(win_inventory);
  pan_map       = new_panel(win_map);
  pan_input     = new_panel(win_input);
  pan_status    = new_panel(win_status);

  // input panel needs to be at the top of the stack initially!
  show_panel(pan_input);

  box(win_inventory,  0, 0);
  box(win_map,        0, 0);
  box(win_input,      0, 0);
  box(win_status,     0, 0);

  // make getch() non-blocking
  nodelay(win_map, true);

  // store the height and width of the displayable win_map
  map_y_size = 25;
  map_x_size = 90;

  // store the height and width of the displayable win_input
  input_y_size = 3;
  input_x_size = 120;

  // initialize input window
  Input = (void *)malloc(360);
  for (int i=0;i<360;i++) {
    Input[i] = ' ';
  }

  // starting x-coord and y-coord
  // temporary, not sticking around
  x = 1 + map_x_size / 2;
  y = 1 + map_y_size / 2;

  // set up signal handling for quitting
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = handle_end_signal;
  sigaction(SIGINT, &action, NULL);
  sigaction(SIGQUIT, &action, NULL);
  sigaction(SIGTERM, &action, NULL);

  // set the game mode
  GameMode = MODE_NORMAL;

  // I'm still running!
  should_quit = FALSE;

  // while initializing the game, I currently need to refresh the screen
  needs_refresh = TRUE;
}

void init_ncurses()
{
  // set up ncurses
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  cbreak();
  nodelay(stdscr, TRUE);
  noecho();
  nonl();
  idlok(stdscr, TRUE);
  intrflush(stdscr, FALSE);
  keypad(stdscr, FALSE);
  curs_set(0);
}

void clean_ncurses()
{
  endwin();
}
