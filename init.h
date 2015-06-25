#include <unistd.h>
#include <signal.h>
#include <locale.h>
#include <ncurses.h>
#include <panel.h>
#include "cell.h"

WINDOW *win_map;
WINDOW *win_inventory;
WINDOW *win_status;
WINDOW *win_input;

PANEL *pan_map;
PANEL *pan_inventory;
PANEL *pan_status;
PANEL *pan_input;

struct sigaction action;
bool should_quit;
bool needs_refresh;
// temporary, represents the character's X,Y coordinates on the current map
int x, y;

// size of the map buffer
int map_x_size, map_y_size;

// size of the input buffer
int input_x_size, input_y_size;

// size of the status buffer
int status_x_size, status_y_size;

// size of the inventory buffer
int inventory_x_size, inventory_y_size;

// the viewable map buffer
char *Map;

// the viewable input buffer
char *Input;

// the viewable status buffer
char *Status;

// the viewable inventory buffer
char *Inventory;

void init_map();
void init_windows();
void init_ncurses();
void clean_ncurses();
