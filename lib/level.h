#pragma once

#include <stdbool.h>
#include <raylib.h>
#include "defines.h"

void draw_level_to_screen(char (*foreground)[GRID_Y]);
char** generate_screen(int stage);
void scroll_level(float distance, char (*foreground)[GRID_Y]);
bool should_generate_screen(char (*level)[GRID_Y]);
