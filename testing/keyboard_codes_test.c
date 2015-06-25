#include <ncurses.h>
#include <locale.h>
#include <stdio.h>

int main(){
  int key_input = ERR;
  int key_1 = ERR;
  int key_2 = ERR;
  int key_3 = ERR;
  int inputs = 0;
  int color;

  setlocale(LC_ALL, "");
  initscr();
  start_color();

  init_pair(7, COLOR_RED, COLOR_BLACK);
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(5, COLOR_CYAN, COLOR_BLACK);
  init_pair(6, COLOR_WHITE, COLOR_BLACK);

  cbreak();
  noecho();
  intrflush(stdscr, FALSE);
  keypad(stdscr, FALSE);
  curs_set(0);

  nodelay(stdscr, TRUE);

  mvprintw(5, 5, "Keyboard codes test.");
  mvprintw(6, 5, "Press keys to see codes.");

  while (1) {
    key_input = getch();
    if (key_input != ERR)
    {
      while (getch() != ERR); // clear keyboard input buffer

      color = COLOR_PAIR(1+(0+inputs)%7);
      attron(color);
      mvprintw(10, 15, "%d\n", (key_2==ERR?0:key_2));
      attroff(color);

      color = COLOR_PAIR(1+(1+inputs)%7);
      attron(color);
      mvprintw(10, 20, "%d\n", (key_1==ERR?0:key_1));
      attroff(color);

      color = COLOR_PAIR(1+(2+inputs)%7);
      attron(color);
      mvprintw(10, 25, "%d\n", (key_input==ERR?0:key_input));
      attroff(color);

      inputs++;

      key_2 = key_1;
      key_1 = key_input;
    }
    napms(100);
  }
  attrset(0);

  endwin();
  return 0;
}
