#pragma once
#include <stdbool.h>

void write_and_open_howtoplay_if_nonexistant();
void write_and_open_credits_if_nonexistant();

void open_text_file(char* path);
bool posix_command_exists(char* command);
