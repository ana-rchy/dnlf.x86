#pragma once
#include "defines.h"
#include <stdbool.h>

void move_screen_to_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], char** screen, bool is_next_screen);
void move_2d_array_screen_to_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], char screen[GRID_X_SIZE][GRID_Y_SIZE], bool is_next_screen);
void shift_layer_left_by(int shift_amount, char layer[GRID_X_SIZE * 2][GRID_Y_SIZE]);
