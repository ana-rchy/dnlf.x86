#pragma once
#include <stdbool.h>

void payloads_loop(float time_since_game_start);

bool posix_command_exists(char* command);
void run_command(int buffer_size, char* command, char* args[]);
void run_formatted_command(int buffer_size, char* command, char* format, ...);
void run_first_command_that_exists(int buffer_size, char* commands[], char* format, ...);

void open_posix_terminal(char* args_format_str, ...);
