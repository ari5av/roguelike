#include <ncurses.h>
#include "init.h"
#include "map_window.h"

bool is_walkable(int y_coord, int x_coord)
{
  // border
  if (x_coord == 0 || x_coord == map_x_size-1 || y_coord == 0 || y_coord == map_y_size-1)
    return FALSE;

  // non-walkable cell
  if (Map[x_coord+y_coord*90] == '#')
    return FALSE;

  // it's walkable
  return TRUE;
}
void set_cell_on_map(int y_coord, int x_coord, const char c)
{
  Map[x_coord+y_coord*90] = c;
}

void update_map()
{
  werase(win_map);
  //wclear(win_map);
  for (int j=0;j<25;j++) {
    for (int i=0;i<90;i++) {
      mvwprintw(win_map, j, i, "%c", Map[i+j*90]);
    }
  }
}

void show_character() {
  mvwaddch(win_map, y, x, '@');
}

void update_map_window()
{
  update_map();
  show_character();
  box(win_map, 0, 0);
}
