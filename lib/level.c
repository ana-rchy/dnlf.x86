#include <stdlib.h>
#include "level.h"
#include "defines.h"
#include "renderer.h"

char level[SCREEN_TEXT_X * 2][SCREEN_TEXT_Y];

void setup_level() {
    for (int x = 0; x < SCREEN_TEXT_X; x++) {
        for (int y = 0; y < SCREEN_TEXT_Y; y++) {
            level[x][y] = T_LINE;
        }
    }
}

void draw_level_to_screen() {
    for (int x = 0; x < SCREEN_TEXT_X; x++) {
        for (int y = 0; y < SCREEN_TEXT_Y; y++) {
            draw_char(level[x][y], x, y);
       }
    }
}

void generate_next_screen(int stage) {
    char new_screen[SCREEN_TEXT_X][SCREEN_TEXT_Y];

    for (int x = 0; x < SCREEN_TEXT_X; x++) {
        for (int y = 0; y < SCREEN_TEXT_Y; y++) {
            new_screen[x][y] = ' ';
       }
    }

    // each iteration creates an air block
    // reduces by 1 for every 3rd stage after 4
    // e.g. stage 0-6 = 6, 7-9 = 5, 10-12 = 4, etc.
    #define MAX_AIR_BLOCKS 6
    #define MIN_AIR_BLOCK_SIZE 2
    #define MAX_AIR_BLOCK_SIZE 8

    int air_blocks_count = MAX_AIR_BLOCKS - (max(stage - 4, 0) / 3);

    for (int i = 0; i < air_blocks_count; i++) {
        int modulo = MAX_AIR_BLOCK_SIZE - MIN_AIR_BLOCK_SIZE + 1;
        int rect_width = (rand() % modulo) + MIN_AIR_BLOCK_SIZE;
        int rect_height = (rand() % modulo) + MIN_AIR_BLOCK_SIZE;

        int rect_x_pos = rand() % (SCREEN_TEXT_X - rect_width);
        int rect_y_pos = rand() % (SCREEN_TEXT_Y - rect_height);

        for (int x = 0; x < rect_width; x++) {
            for (int y = 0; y < rect_height; y++) {
                int off_x = rand() % 2;
                int off_y = rand() % 2;
           }
        }
    }



    for (int x = 0; x < SCREEN_TEXT_X; x++) {
        for (int y = 0; y < SCREEN_TEXT_Y; y++) {
            level[x][y] = new_screen[x][y];
       }
    }
}
