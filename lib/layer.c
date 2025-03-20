#include "layer.h"
#include "defines.h"
#include <stdio.h>

void move_screen_to_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], char** screen, bool is_next_screen) {
    int start_x = is_next_screen ? GRID_X_SIZE : 0;

    for (int x = 0; x < GRID_X_SIZE; x++) {
        for (int y = 0; y < GRID_Y_SIZE; y++) {
            layer[start_x + x][y] = screen[x][y];
        }
    }

    for (int x = 0; x < GRID_X_SIZE; x++) {
        free(screen[x]);
    }

    free(screen);
}

// this exists because [x][y] works differently between 2d arrays and **. thanks obama
void move_2d_array_screen_to_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], char screen[GRID_X_SIZE][GRID_Y_SIZE], bool is_next_screen) {
    int start_x = is_next_screen ? GRID_X_SIZE : 0;

    for (int x = 0; x < GRID_X_SIZE; x++) {
        for (int y = 0; y < GRID_Y_SIZE; y++) {
            layer[start_x + x][y] = screen[x][y];
        }
    }
}

void shift_layer_left_by(int shift_amount, char layer[GRID_X_SIZE * 2][GRID_Y_SIZE]) {
    if (shift_amount < 1) {
        printf("shift_layer_left_by: shift_amount is < 1 (%d)\n", shift_amount);
        return;
    }

    for (int y = 0; y < GRID_Y_SIZE; y++) {
        for (int x = shift_amount; x < GRID_X_SIZE * 2; x++) {
            layer[x - shift_amount][y] = layer[x][y];
        }
        
        // clear columns that havent been replaced by smth else
        for (int x = GRID_X_SIZE * 2 - shift_amount; x < GRID_X_SIZE * 2; x++) {
            layer[x][y] = ' ';
        }
    } 
}
