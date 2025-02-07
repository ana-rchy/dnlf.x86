#include <stdio.h>
#include <raylib.h>
#include "renderer.h"
#include "defines.h"

Font font;

void setup_renderer() {
    font = LoadFont("font.png");
}

void draw_char(char c, int x, int y, Color fg_color, Color bg_color) {
    if (x >= GRID_X || y >= GRID_Y) {
        printf("given char pos out of bounds: %d %d\n", x, y);
        return;
    }

    Vector2 pos = { x * UNIT_X, y * UNIT_Y };
            
    // guarantee a string with a single char in it,
    // in an array it might be interpreted differently
    char chr[2];
    sprintf(chr, "%c", c);
    
    DrawRectangle(pos.x, pos.y, UNIT_X, UNIT_Y, bg_color);
    DrawTextEx(font, chr, pos, 12, 0, fg_color);
}

// 'char (*foreground)[GRID_Y]' means you can pass in a 2d array
void draw_level_to_screen(Color fg_color, Color bg_color, char foreground[GRID_X * 2][GRID_Y], char background_1[GRID_X * 2][GRID_Y], char background_2[GRID_X * 2][GRID_Y]) {
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            draw_char(background_2[x][y], x, y, fg_color, bg_color);

            if (background_1[x][y] != ' ') {
                draw_char(background_1[x][y], x, y, fg_color, bg_color);
            }

            if (foreground[x][y] != ' ') {
                draw_char(foreground[x][y], x, y, fg_color, bg_color);
            }
       }
    }
}
