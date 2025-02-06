#include <raylib.h>
#include <stdlib.h>
#include <math.h>
#include "level.h"
#include "defines.h"
#include "renderer.h"

// reimplementation of the 'geometry' function
char** generate_blocks(int stage, char chr) {
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
                    // this does the texture but i aint figuring out the formula sorry lol
                    /*new_screen[rect_abs_x_pos + x][rect_abs_y_pos + y] = (char) ( (sin(y * (stage+1)) * cos(x*x) * 2) + 2 ) + 220;*/

                    // consts are char values
                    new_screen[rect_abs_x_pos + x][rect_abs_y_pos + y] = rand_range(UP_HALF, RIGHT_HALF);
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
                        new_screen[rect_abs_x_pos + x][y] = rand_range(UP_HALF, RIGHT_HALF);
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
                        // TODO: og is 'm[l(i,j)] = (sin(j*(stage+1))*cos(i*iframes+1)*2+2)+220;', gotta put in iframes instead ig
                        new_screen[rect_abs_x_pos + x][y] = rand_range(UP_HALF, RIGHT_HALF);
                    }
                }
            }
        }
    }

    return new_screen;
}

// TODO: make this function more readable jfc
void add_rods(char (*layer)[GRID_Y], char chr) {
    // TODO: verify length of x array

    for (int x = GRID_X; x < GRID_X * 2; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            int pt = -1;
            
            // bias towards vertical rods cause it checks for walls up and down for vertical,
            // but only to the left for horizontal
            if (layer[x][y] == ' ') {
                // -1 for length to index, -1 to be not on the edge
                if (y <= GRID_Y - 2 && layer[x][y + 1] == chr) {
                    pt = 1;
                }
                if (x >= GRID_X + 1 && layer[x - 1][y] == chr) {
                    pt = 2;
                }
                if (y >= 1 && layer[x][y - 1] == chr) {
                    pt = 3;
                }
            }

            if (pt == -1 || rand_range(1, 64) != 1) {
                continue;
            }

            switch (pt) {
            case 1:
                for (int y2 = y; y2 >= 0 && layer[x][y2] != chr; y2--) {
                    layer[x][y2] = VERT_LINE;
                }
                break;

            case 2:
                for (int x2 = x; x2 < GRID_X * 2 && layer[x2][y] != chr; x2++) {
                    if (rand_range(1, 10) == 1) {
                        layer[x2][y] = DOWN_T_LINE;
                    } else {
                        layer[x2][y] = HORIZ_LINE;
                    }
                }
                break;

            case 3:
                for (int y2 = y; y2 < GRID_Y && layer[x][y2] != chr; y2++) {
                    layer[x][y2] = VERT_LINE;
                }
                break;
            }
        }
    }

    for (int y = 0; y < GRID_Y; y++) {
        // this should actually check if it could be a T too,
        // but we preserving all the bugs here so, Too bad!
        if (layer[GRID_X - 1][y] == HORIZ_LINE && layer[GRID_X][y] == ' ') {
            for (int x = GRID_X; x < GRID_X * 2 && layer[x][y] != chr; x++) {
                layer[x][y] = HORIZ_LINE;
            }
        }
    }

    for (int x = GRID_X; x < GRID_X * 2; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            bool leftwards = false;
            bool rightwards = false;
            bool upwards = false;
            bool downwards = false;

            if (x >= GRID_X + 1 && layer[x - 1][y] == HORIZ_LINE) {
                leftwards = true;
            }
            if (x <= (GRID_X*2) - 2 && layer[x + 1][y] == HORIZ_LINE) {
                rightwards = true;
            }
            if (y >= 1 && layer[x][y - 1] == VERT_LINE) {
                upwards = true;
            }
            if (y <= GRID_Y - 2 && layer[x][y + 1] == VERT_LINE) {
                downwards = true;
            }

            if (leftwards && rightwards && upwards && downwards) {
                layer[x][y] = PLUS_LINE;
            } else if (rightwards && upwards && downwards) {
                layer[x][y] = LEFT_T_LINE;
            } else if (leftwards && upwards && downwards) {
                layer[x][y] = RIGHT_T_LINE;
            } else if (leftwards && rightwards && upwards ) {
                layer[x][y] = UP_T_LINE;
            } else if (leftwards && rightwards && downwards) {
                layer[x][y] = DOWN_T_LINE;
            }
        }
    }
}

bool should_generate_screen(char (*layer)[GRID_Y]) {
    // TODO: verify length of x array

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

//////////////////////////////////////////////////////////////////

void setup_layer(char chr, char (*layer)[GRID_Y]) {
    char** new_screen = generate_blocks(0, chr);
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            layer[x][y] = new_screen[x][y];
        }
    }

    new_screen = generate_blocks(0, chr);
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            layer[GRID_X + x][y] = new_screen[x][y];
        }
    }

    add_rods(layer, chr);
}

void extend_layer_if_needed(char chr, char (*layer)[GRID_Y]) {
    if (!should_generate_screen(layer)) {
        return;
    }

    char** new_screen = generate_blocks(0, chr);
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            layer[GRID_X + x][y] = new_screen[x][y];
        }
    }

    add_rods(layer, chr);
}

//////////////////////////////////////////////////////////////////

void scroll_layer(char (*layer)[GRID_Y]) {
    for (int y = 0; y < GRID_Y; y++) {
        for (int x = 1; x < GRID_X * 2; x++) {
            layer[x - 1][y] = layer[x][y];
        }

        layer[GRID_X * 2 - 1][y] = ' ';
    }
}

void scroll_and_extend_layer(float distance, char (*layer)[GRID_Y], float* distance_overflow) {
    // TODO: verify length of x array

    *distance_overflow += fmod(distance, 1);

    if (*distance_overflow >= 1) {
        distance += (int) *distance_overflow;
        *distance_overflow = fmod(*distance_overflow, 1);
    }

    for (int i = 0; i < (int) distance; i++) {
        scroll_layer(layer);
    }
}
