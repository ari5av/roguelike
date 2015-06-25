#include <ncurses.h>
#include "init.h"
#include "input_window.h"

void set_cell_on_input(int y, int x, const char c)
{
  Input[x+y*120] = c;
}

void update_input()
{
  werase(win_input);
  for (int j=0;j<3;j++) {
    for (int i=0;i<120;i++) {
      mvwprintw(win_input, j, i, "%c", Input[i+j*120]);
    }
  }
}

void update_input_window()
{
  update_input();
  box(win_input, 0, 0);
}
