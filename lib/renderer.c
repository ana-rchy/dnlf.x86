#include <stdio.h>
#include <raylib.h>
#include "renderer.h"

char screen[GRID_X][GRID_Y] = {};
static Font font;

void setup_renderer() {
    font = LoadFont("font.png");
}

void draw_char(char c, int x, int y) {
    if (x >= GRID_X || y >= GRID_Y) {
        printf("given char pos out of bounds: %d %d\n", x, y);
        return;
    }

    Vector2 pos = { x * UNIT_X, y * UNIT_Y };
            
    // guarantee a string with a single char in it,
    // in an array it might be interpreted differently
    char chr[2];
    sprintf(chr, "%c", c);

    DrawTextEx(font, chr, pos, 12, 0, BLACK);
}

void draw_screen() {
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            Vector2 pos = { x * UNIT_X, y * UNIT_Y };
            
            // guarantee a string with a single char in it,
            // in an array it might be interpreted differently
            char* chr;
            sprintf(chr, "%c", screen[x][y]);

            DrawTextEx(font, chr, pos, 12, 0, BLACK);
        }
    }
}
