#include "level_gen.h"
#include <math.h>
#include <raylib.h>

// reimplementation of the 'geometry' function
char** generate_blocks(int stage, char chr, int invul_frames) {
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
        int rect_width = rand_range(MIN_AIR_BLOCK_SIZE, MAX_AIR_BLOCK_SIZE);
        int rect_height = rand_range(MIN_AIR_BLOCK_SIZE, MAX_AIR_BLOCK_SIZE);
        
        // rectangle absolute x/y pos
        int rect_abs_x_pos = rand_range(0, GRID_X - rect_width);
        int rect_abs_y_pos = rand_range(0, GRID_Y - rect_height);
        
        // assumes a block starting from 0, 0
        // before actually putting it in the correct position in the new screen
        for (int x = 0; x < rect_width; x++) {
            for (int y = 0; y < rect_height; y++) {
                // edges will be full blocks, the inside is textured with non-full blocks
                // rand_range() for either 1 thick or 2 thick edges
                int edge_width = rand_range(0, 1);
                int edge_height = rand_range(0, 1);

                if ( (x <= edge_width || x >= rect_width - edge_width - 1) ||
                     (y <= edge_height || y >= rect_height - edge_height - 1) ||
                     chr != FULL_BLOCK)
                {
                    new_screen[rect_abs_x_pos + x][rect_abs_y_pos + y] = chr;
                } else {
                    new_screen[rect_abs_x_pos + x][rect_abs_y_pos + y] = weird_texture_formula(x, y, stage, -1);
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
        int rect_width = rand_range(0, (GRID_X / 3) - 1);
        int rect_height;
        int rect_abs_x_pos = rand_range(0, GRID_X - rect_width);
        bool on_ceiling = rand_range(0, 1);
        
        // stage 0-3 = 4 tall edge blocks, 4-7 = 3, ..., >= 16 = 0 tall blocks
        //
        // the higher the stage, the lower the probability of a tall block generating in any one screen
        // e.g. stage 0 = 1/5 chance, 1 = 1/10, 2 = 1/15, etc.
        if (the_big_one < (MAX_TALL_EDGE_BLOCKS - (stage/4)) && rand_range(1, (stage+1) * 5) == 1) {
            rect_height = rand_range(0, (GRID_Y / 2) - 1);
            the_big_one++;
        } else {
            rect_height = rand_range(0, (GRID_Y / 2) - (MIN_SHORT_TALL_BLOCK_DIFFERENCE - stage) - 1);
        }

        if (on_ceiling) {
            for (int x = 0; x < rect_width; x++) {
                for (int y = 0; y < rect_height; y++) {
                    int edge_width = rand_range(0, 2);
                    int edge_height = rand_range(0, 2);

                    if ( (x <= edge_width || x >= rect_width - edge_width - 1) ||
                         (y <= edge_height || y >= rect_height - edge_height - 1) ||
                         chr != FULL_BLOCK)
                    {
                        new_screen[rect_abs_x_pos + x][y] = chr;
                    } else {
                        new_screen[rect_abs_x_pos + x][y] = weird_texture_formula(x, y, stage, -1);
                    }
                }
            }
        } else {
            for (int x = 0; x < rect_width; x++) {
                for (int y = GRID_Y - 1; y >= GRID_Y - rect_height; y--) {
                    int edge_width = rand_range(0, 4);
                    int edge_height = rand_range(0, 4);

                    if ( (x <= edge_width || x >= rect_width - edge_width - 1) ||
                         (y >= GRID_Y - edge_height - 1 || y <= GRID_Y - rect_height + edge_height) ||
                         chr != FULL_BLOCK)
                    {
                        new_screen[rect_abs_x_pos + x][y] = chr;
                    } else {
                        new_screen[rect_abs_x_pos + x][y] = weird_texture_formula(x, y, stage, invul_frames);
                    }
                }
            }
        }
    }

    return new_screen;
}

char weird_texture_formula(int x, int y, int stage, int invul_frames) {
    // the ANSI code for upper-half block is 224, but the formula never seems to actually go up to 224
    // but somehow in the og, that result DOESNT go to 223 when truncating, it goes to 224
    // whereas when i was testing it, it does (windows vs linux difference?)
    //
    // the issue is: i dont know at what threshold 223.xxxxx goes to 224 in the og
    // so im just gonna guess and make the threshold 223.9
    //
    // TODO: figure out how to do this accurately to the OG
    
    float formula_result;
    if (invul_frames == -1) {
        formula_result = ( sin(y * (stage+1)) * cos(x*x) * 2 ) + 2 + 220;
    } else {
        // dont ask me why iframes are used
        formula_result = ( sin(y * (stage+1)) * cos(x*invul_frames + 1) * 2 ) + 2 + 220;
    }
    
    if (formula_result > 223.9) {
        formula_result = 224.0;
    }

    switch ((int) formula_result) {
        case 220:
            return FULL_BLOCK;
        
        case 221:
            return DOWN_HALF;

        case 222:
            return LEFT_HALF;

        case 223:
            return RIGHT_HALF;

        case 224:
            return UP_HALF;

        default:
            return FULL_BLOCK;
    }
}

//////////////////////////////////////////////////////////////////

bool should_generate_screen(char layer[GRID_X * 2][GRID_Y]) {
    bool should_generate = true;

    for (int x = GRID_X; x < GRID_X * 2; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            if (layer[x][y] != ' ') {
                should_generate = false;
            }
        }
    }

    return should_generate;
}
