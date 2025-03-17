#pragma once
#include "defines.h"

void setup_layer(char layer[GRID_X * 2][GRID_Y], char chr);
void setup_foreground(char layer[GRID_X * 2][GRID_Y]);
void extend_layer_if_needed(char layer[GRID_X * 2][GRID_Y], int stage, char chr, int invul_frames);

void scroll_layer(char layer[GRID_X * 2][GRID_Y]);
void scroll_and_extend_layer(char layer[GRID_X * 2][GRID_Y], int stage, char chr, float distance, float* distance_overflow, int invul_frames);
