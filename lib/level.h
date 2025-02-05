#pragma once

#include <stdbool.h>
#include <raylib.h>
#include "defines.h"

char** generate_screen(int stage, char chr);
bool should_generate_screen(char (*level)[GRID_Y]);

void setup_layer(char chr, char (*layer)[GRID_Y]);
void extend_layer_if_needed(char chr, char (*layer)[GRID_Y]);

void scroll_layer(float distance, char (*layer)[GRID_Y], float* distance_overflow);
