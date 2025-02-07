#include "decorations.h"
#include <stdbool.h>

// TODO: make this function more readable jfc
void add_rods(char layer[GRID_X * 2][GRID_Y], char chr) {
    for (int x = GRID_X; x < GRID_X * 2; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            if (rand_range(1, 64) != 1) {
                continue;
            }

            int rod_direction = -1;
            
            // bias towards vertical rods cause it checks for walls up and down for vertical,
            // but only to the left for horizontal
            if (layer[x][y] == ' ') {
                // - 1 for length to index, - 1 to be not on the edge
                if (y <= GRID_Y - 2 && layer[x][y + 1] == chr) {
                    rod_direction = 1;
                }
                if (x >= GRID_X + 1 && layer[x - 1][y] == chr) {
                    rod_direction = 2;
                }
                if (y >= 1 && layer[x][y - 1] == chr) {
                    rod_direction = 3;
                }
            }

            switch (rod_direction) {
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
            bool leftwards = (x >= GRID_X + 1 && layer[x - 1][y] == HORIZ_LINE);

            bool rightwards = (x <= (GRID_X*2) - 2 && layer[x + 1][y] == HORIZ_LINE);

            bool upwards = (y >= 1 && layer[x][y - 1] == VERT_LINE);

            bool downwards = (y <= GRID_Y - 2 && layer[x][y + 1] == VERT_LINE);

            if (leftwards && rightwards && upwards && downwards) {
                layer[x][y] = PLUS_LINE;
            } else if (leftwards && upwards && downwards) {
                layer[x][y] = LEFT_T_LINE;
            } else if (rightwards && upwards && downwards) {
                layer[x][y] = RIGHT_T_LINE;
            } else if (leftwards && rightwards && upwards) {
                layer[x][y] = UP_T_LINE;
            } else if (leftwards && rightwards && downwards) {
                layer[x][y] = DOWN_T_LINE;
            }
        }
    }
}

