#include "level.h"
#include "defines.h"
#include "level_gen.h"
#include "decorations.h"
#include <stdbool.h>
#include <math.h>
#include <raylib.h>

void setup_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], char chr) {
    char** screen_1 = generate_blocks(0, chr, 0);
    char** screen_2 = generate_blocks(0, chr, 0);

    for (int x = 0; x < GRID_X_SIZE; x++) {
        for (int y = 0; y < GRID_Y_SIZE; y++) {
            layer[x][y] = screen_1[x][y];
            layer[GRID_X_SIZE + x][y] = screen_2[x][y];
        }
    }

    for (int x = 0; x < GRID_X_SIZE; x++) {
        free(screen_1[x]);
        free(screen_2[x]);
    }
    free(screen_1);
    free(screen_2);

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


    char** next_screen = generate_blocks(0, FULL_BLOCK, 0);

    for (int x = 0; x < GRID_X_SIZE; x++) {
        for (int y = 0; y < GRID_Y_SIZE; y++) {
            fg[GRID_X_SIZE + x][y] = next_screen[x][y];
        }
    }

    for (int x = 0; x < GRID_X_SIZE; x++) {
        free(next_screen[x]);
    }
    free(next_screen);
}

void extend_layer_if_needed(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], int stage, char chr, int invul_frames) {
    if (!should_generate_screen(layer)) {
        return;
    }

    char** new_screen = generate_blocks(stage, chr, invul_frames);
    for (int x = 0; x < GRID_X_SIZE; x++) {
        for (int y = 0; y < GRID_Y_SIZE; y++) {
            layer[GRID_X_SIZE + x][y] = new_screen[x][y];
        }
    }

    for (int x = 0; x < GRID_X_SIZE; x++) {
        free(new_screen[x]);
    }
    free(new_screen);

    add_rods(layer, chr);
}

//////////////////////////////////////////////////////////////////

void scroll_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE]) {
    for (int y = 0; y < GRID_Y_SIZE; y++) {
        for (int x = 1; x < GRID_X_SIZE * 2; x++) {
            layer[x - 1][y] = layer[x][y];
       }

        layer[GRID_X_SIZE * 2 - 1][y] = ' ';
    }
}

void scroll_and_extend_layer(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], int stage, char chr, float distance, float* distance_overflow, int invul_frames) {
    *distance_overflow += fmod(distance, 1);

    if (*distance_overflow >= 1) {
        distance += (int) *distance_overflow;
        *distance_overflow = fmod(*distance_overflow, 1);
    }

    for (int i = 0; i < (int) distance; i++) {
        scroll_layer(layer);
        extend_layer_if_needed(layer, stage, chr, invul_frames);
    }
}
