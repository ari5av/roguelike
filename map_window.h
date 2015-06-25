#include <ncurses.h>
#include <panel.h>

bool is_walkable(int, int);
void set_cell_on_map(int, int, const char);
void update_map();
void show_character();
void update_map_window();
