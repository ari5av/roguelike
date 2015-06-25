#define MAX_COMMAND_LEN 40

char command_buffer[MAX_COMMAND_LEN];
int command_size;

void enter_command_mode();
void add_char_to_command(int);
void backspace_command();
void execute_command();
void exit_command_mode();
