#pragma once
#include <stdbool.h>
#include "defines.h"

char** generate_blocks(int stage, char chr);
char weird_texture_formula(int x, int y, int stage);

bool should_generate_screen(char layer[GRID_X * 2][GRID_Y]);
