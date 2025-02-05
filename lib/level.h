#pragma once

#include <stdbool.h>
#include <raylib.h>
#include "defines.h"

void draw_level_to_screen(char (*foreground)[GRID_Y], char (*background_1)[GRID_Y], char (*background_2)[GRID_Y]);
char** generate_screen(int stage, char chr);
void scroll_layer(float distance, char (*layer)[GRID_Y], float* distance_overflow);
bool should_generate_screen(char (*level)[GRID_Y]);
void setup_layer(char chr, char (*layer)[GRID_Y]);
void extend_layer_if_needed(char chr, char (*layer)[GRID_Y]);
