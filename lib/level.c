#include "level.h"
#include "defines.h"
#include "level_gen.h"
#include "decorations.h"
#include "layer.h"
#include <stdbool.h>
#include <math.h>
#include <raylib.h>

void setup_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], char chr) {
    move_screen_to_layer(layer, generate_blocks(0, chr, 0), false);
    move_screen_to_layer(layer, generate_blocks(0, chr, 0), true);
    
    add_rods(layer, chr);
}

void setup_foreground(char fg[GRID_X_SIZE * 2][GRID_Y_SIZE]) {
    for (int x = 0; x < GRID_X_SIZE; x++) {
        for (int y = 0; y < GRID_Y_SIZE; y++) {
            fg[x][y] = ' ';
       }
    }

    for (int x = 0; x < 76; x++) {
        for (int y = 0; y < 12; y++) {
            if ((x % 8) < 4) {
                fg[x][y] = FULL_BLOCK;
            }
        }
    }

    for (int x = 0; x < 76; x++) {
        for (int y = GRID_Y_SIZE - 12; y < GRID_Y_SIZE; y++) {
            if ((x % 8) < 4) {
                fg[x][y] = FULL_BLOCK;
            }
        }
    }

    for (int x = 0; x < 96; x++) {
        for (int y = 12; y < 12 + 8; y++) {
            fg[x][y] = FULL_BLOCK;
        }
    }

    for (int x = 0; x < 96; x++) {
        for (int y = GRID_Y_SIZE - 12 - 8; y < GRID_Y_SIZE - 12; y++) {
            fg[x][y] = FULL_BLOCK;
        }
    }


    move_screen_to_layer(fg, generate_blocks(0, FULL_BLOCK, 0), true);
}

void extend_layer_if_needed(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], int stage, char chr, int invul_frames) {
    if (!should_generate_screen(layer)) {
        return;
    }

    move_screen_to_layer(layer, generate_blocks(stage, chr, invul_frames), true);
    add_rods(layer, chr);
}

//////////////////////////////////////////////////////////////////

void shift_left_and_extend_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], int stage, char chr, float distance, float* distance_overflow, int invul_frames) {
    *distance_overflow += fmod(distance, 1);

    if (*distance_overflow >= 1) {
        distance += (int) *distance_overflow;
        *distance_overflow = fmod(*distance_overflow, 1);
    }

    for (int i = 0; i < (int) distance; i++) {
        shift_layer_left_by(1, layer);
        extend_layer_if_needed(layer, stage, chr, invul_frames);
    }
}
