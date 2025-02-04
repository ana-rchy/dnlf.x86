#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include "level.h"
#include "defines.h"
#include "renderer.h"

// 'char (*foreground)[GRID_Y]' means you can pass in a 2d array
void draw_level_to_screen(char (*foreground)[GRID_Y]) {
    // TODO: verify length of x array

    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            draw_char(foreground[x][y], x, y);
       }
    }
}

// reimplementation of the 'geometry' function
char** generate_screen(int stage) {
    // idk why this syntax works but sure
    char** new_screen = malloc(GRID_X * sizeof(char*));
    for (int x = 0; x < GRID_X; x++) {
        new_screen[x] = malloc(GRID_Y * sizeof(char));
    }

    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            new_screen[x][y] = ' ';
       }
    }

    // each iteration creates an air block
    // decreases by 1 for every 3rd stage after 4
    // e.g. stage 0-6 = 6, 7-9 = 5, 10-12 = 4, etc.
    int air_blocks_count = MAX_AIR_BLOCKS - (max(stage - 4, 0) / 3);

    for (int i = 0; i < air_blocks_count; i++) {
        int rect_width = GetRandomValue(MIN_AIR_BLOCK_SIZE, MAX_AIR_BLOCK_SIZE);
        int rect_height = GetRandomValue(MIN_AIR_BLOCK_SIZE, MAX_AIR_BLOCK_SIZE);
        
        // rectangle absolute x/y pos
        int rect_abs_x_pos = GetRandomValue(0, GRID_X - rect_width);
        int rect_abs_y_pos = GetRandomValue(0, GRID_Y - rect_height);
        
        // assumes a block starting from 0, 0
        // before actually putting it in the correct position in the new screen
        for (int x = 0; x < rect_width; x++) {
            for (int y = 0; y < rect_height; y++) {
                // edges will be full blocks, the inside is textured with non-full blocks
                // GetRandomValue() for either 1 thick or 2 thick edges
                int edge_width = GetRandomValue(0, 1);
                int edge_height = GetRandomValue(0, 1);

                if ( (x <= edge_width || x >= rect_width - edge_width - 1) ||
                     (y <= edge_height || y >= rect_height - edge_height - 1) )
                {
                    new_screen[rect_abs_x_pos + x][rect_abs_y_pos + y] = FULL_BLOCK;
                } else {
                    // this does the texture but i aint figuring out the formula sorry lol
                    /*new_screen[rect_abs_x_pos + x][rect_abs_y_pos + y] = (char) ( (sin(y * (stage+1)) * cos(x*x) * 2) + 2 ) + 220;*/

                    // consts are char values
                    new_screen[rect_abs_x_pos + x][rect_abs_y_pos + y] = GetRandomValue(UP_HALF, RIGHT_HALF);
                }
           }
        }
    }

    // each iteration creates a ground/ceiling block
    // decreases by 1 for every 2nd stage
    // e.g. stage 0-1 = 16, 2-3 = 15, 4-5 = 14, etc.

    // used for limiting the amount of tall edge blocks that get generated
    int the_big_one = 0;
    
    for (int i = 0; i < MAX_EDGE_BLOCKS - (stage/2); i++) {
        int rect_width = GetRandomValue(0, (GRID_X / 3) - 1);
        int rect_height;
        int rect_abs_x_pos = GetRandomValue(0, GRID_X - rect_width);
        bool on_ceiling = GetRandomValue(0, 1);
        
        // stage 0-3 = 4 tall edge blocks, 4-7 = 3, ..., >= 16 = 0 tall blocks
        //
        // the higher the stage, the lower the probability of a tall block generating in any one screen
        // e.g. stage 0 = 1/5 chance, 1 = 1/10, 2 = 1/15, etc.
        if (the_big_one < (MAX_TALL_EDGE_BLOCKS - (stage/4)) && GetRandomValue(1, (stage+1) * 5) == 1) {
            rect_height = GetRandomValue(0, (GRID_Y / 2) - 1);
            the_big_one++;
        } else {
            rect_height = GetRandomValue(0, (GRID_Y / 2) - (MIN_SHORT_TALL_BLOCK_DIFFERENCE - stage) - 1);
        }

        if (on_ceiling) {
            for (int x = 0; x < rect_width; x++) {
                for (int y = 0; y < rect_height; y++) {
                    int edge_width = GetRandomValue(0, 2);
                    int edge_height = GetRandomValue(0, 2);

                    if ( (x <= edge_width || x >= rect_width - edge_width - 1) ||
                         (y <= edge_height || y >= rect_height - edge_height - 1) )
                    {
                        new_screen[rect_abs_x_pos + x][y] = FULL_BLOCK;
                    } else {
                        new_screen[rect_abs_x_pos + x][y] = GetRandomValue(UP_HALF, RIGHT_HALF);
                    }
                }
            }
        } else {
            for (int x = 0; x < rect_width; x++) {
                for (int y = GRID_Y - 1; y >= GRID_Y - rect_height; y--) {
                    int edge_width = GetRandomValue(0, 4);
                    int edge_height = GetRandomValue(0, 4);

                    if ( (x <= edge_width || x >= rect_width - edge_width - 1) ||
                         (y >= GRID_Y - edge_height - 1 || y <= GRID_Y - rect_height + edge_height) )
                    {
                        new_screen[rect_abs_x_pos + x][y] = FULL_BLOCK;
                    } else {
                        // TODO: og is 'm[l(i,j)] = (sin(j*(stage+1))*cos(i*iframes+1)*2+2)+220;', gotta put in iframes instead ig
                        new_screen[rect_abs_x_pos + x][y] = GetRandomValue(UP_HALF, RIGHT_HALF);
                    }
                }
            }
        }
    }

    return new_screen;
}

float distance_overflow = 0;
void scroll_level(float distance, char (*foreground)[GRID_Y]) {
    // TODO: verify length of x array
    
    distance_overflow += fmod(distance, 1);

    if (distance_overflow >= 1) {
        distance += (int) distance_overflow;
        distance_overflow = fmod(distance_overflow, 1);
    }
    
    for (int i = 0; i < (int) distance; i++) {
        for (int y = 0; y < GRID_Y; y++) {
            for (int x = 1; x < GRID_X * 2; x++) {
                foreground[x - 1][y] = foreground[x][y];
            }

            foreground[GRID_X * 2 - 1][y] = ' ';
        }
    }
}

bool should_generate_screen(char (*level)[GRID_Y]) {
    // TODO: verify length of x array

    bool should_generate = true;

    for (int x = GRID_X; x < GRID_X * 2; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            if (level[x][y] != ' ') {
                should_generate = false;
            }
        }
    }

    return should_generate;
}
