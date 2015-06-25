#include <stdlib.h>
#include <ncurses.h>
#include <panel.h>
#include "init.h"
#include "game.h"
#include "map_window.h"
#include "input_window.h"

int main()
{

  int key_input;
  should_quit = FALSE;

  init_ncurses();
  init_windows();
  init_map();

        // test map...
        for (int j=5;j<20;j++)
          for (int i=5;i<20;i++)
            set_cell_on_map(j, i, '#');
        for (int j=6;j<19;j++)
          for (int i=6;i<19;i++)
            set_cell_on_map(j, i, '.');

  do {
    if (needs_refresh) {
      update_map_window();
      update_input_window();
      update_panels();
      doupdate();
      //napms(30);
      
      // don't need to update screen anymore...
      needs_refresh = FALSE;
    }

    // rest for 10ms inbetween game ticks
    napms(10);
    game_tick();
  } while (!should_quit);

  clean_ncurses();

  return 0;
}
