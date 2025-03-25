#pragma once
#include <stdbool.h>

bool posix_command_exists(char* command);
void run_command(char* command, char* args[]);

int get_first_valid_command_index(char* commands[]);
void run_first_valid_command(char* commands[], char* args[]);

void open_posix_terminal(char* args[]);
