#include <stdio.h>
#include <raylib.h>
#include "renderer.h"

char screen[SCREEN_TEXT_X][SCREEN_TEXT_Y] = {};
static Font font;

void setup_renderer() {
    InitWindow(SCREEN_X, SCREEN_Y, "DO NOT LOSE FOCUS.x86");
    font = LoadFont("font.png");
}

void refresh_screen() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void draw_char(char c, int x, int y) {
    if (x >= SCREEN_TEXT_X || y >= SCREEN_TEXT_Y) {
        printf("given char pos out of bounds: %d %d\n", x, y);
        return;
    }

    screen[x][y] = c;
}

void draw_screen() {
    for (int x = 0; x < SCREEN_TEXT_X; x++) {
        for (int y = 0; y < SCREEN_TEXT_Y; y++) {
            Vector2 pos = { x * UNIT_X, y * UNIT_Y };
            
            // guarantee a string with a single char in it,
            // in an array it might be interpreted differently
            char* chr;
            sprintf(chr, "%c", screen[x][y]);

            DrawTextEx(font, chr, pos, 12, 0, BLACK);
        }
    }

    EndDrawing();
}
