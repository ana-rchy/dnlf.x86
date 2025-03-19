#pragma once
#include "defines.h"
#include "player.h"
#include <stdbool.h>

char** generate_blocks(int stage, char chr, int invul_frames);
char weird_texture_formula(int x, int y, int stage, int invul_frames);

bool should_generate_screen(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE]);
