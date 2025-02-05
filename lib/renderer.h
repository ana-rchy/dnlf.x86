#pragma once

#include <raylib.h>
#include "defines.h"

void setup_renderer();
void draw_char(char c, int x, int y);
void draw_level_to_screen(char (*foreground)[GRID_Y], char (*background_1)[GRID_Y], char (*background_2)[GRID_Y]);
