#include "level.h"
#include "level_gen.h"
#include "decorations.h"
#include <stdbool.h>
#include <math.h>
#include <raylib.h>

void setup_layer(char chr, char layer[GRID_X * 2][GRID_Y]) {
    char** screen_1 = generate_blocks(0, chr);
    char** screen_2 = generate_blocks(0, chr);

    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            layer[x][y] = screen_1[x][y];
            layer[GRID_X + x][y] = screen_2[x][y];
        }
    }

    for (int x = 0; x < GRID_X; x++) {
        free(screen_1[x]);
        free(screen_2[x]);
    }
    free(screen_1);
    free(screen_2);

    add_rods(layer, chr);
}

void extend_layer_if_needed(int stage, char chr, char layer[GRID_X * 2][GRID_Y]) {
    if (!should_generate_screen(layer)) {
        return;
    }

    char** new_screen = generate_blocks(stage, chr);
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            layer[GRID_X + x][y] = new_screen[x][y];
        }
    }

    for (int x = 0; x < GRID_X; x++) {
        free(new_screen[x]);
    }
    free(new_screen);

    add_rods(layer, chr);
}

//////////////////////////////////////////////////////////////////

void scroll_layer(char layer[GRID_X * 2][GRID_Y]) {
    for (int y = 0; y < GRID_Y; y++) {
        for (int x = 1; x < GRID_X * 2; x++) {
            layer[x - 1][y] = layer[x][y];
       }

        layer[GRID_X * 2 - 1][y] = ' ';
    }
}

void scroll_and_extend_layer(char layer[GRID_X * 2][GRID_Y], int stage, char chr, float distance, float* distance_overflow) {
    *distance_overflow += fmod(distance, 1);

    if (*distance_overflow >= 1) {
        distance += (int) *distance_overflow;
        *distance_overflow = fmod(*distance_overflow, 1);
    }

    for (int i = 0; i < (int) distance; i++) {
        scroll_layer(layer);
        extend_layer_if_needed(stage, chr, layer);
    }
}
