#pragma once
#include "defines.h"

void setup_layer(char chr, char layer[GRID_X * 2][GRID_Y]);
void extend_layer_if_needed(char chr, char layer[GRID_X * 2][GRID_Y]);

void scroll_layer(char layer[GRID_X * 2][GRID_Y]);
void scroll_and_extend_layer(char layer[GRID_X * 2][GRID_Y], char chr, float distance, float* distance_overflow);
