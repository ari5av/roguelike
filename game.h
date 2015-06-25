#include <ncurses.h>

typedef enum {
  MODE_NORMAL = 1,
  MODE_COMMAND,
  MODE_WAITING,
  MODE_SELECTING,
  MODE_ANIMATION
} game_mode_t;

game_mode_t GameMode;

void handle_end_signal(int);
void handle_keypress_normal(int);
void handle_keypress_command(int);
void handle_keypress_waiting(int);
void handle_keypress_selecting(int);
void game_tick();
