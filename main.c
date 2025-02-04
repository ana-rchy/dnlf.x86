#include <stdio.h>
#include <raylib.h>
#include "lib/defines.h"
#include "lib/renderer.h"
#include "lib/level.h"

int main() {
    char foreground[GRID_X * 2][GRID_Y];
    /*char** foreground = malloc(GRID_X * 2 * sizeof(char*));*/
    /*for (int x = 0; x < GRID_X; x++) {*/
    /*    foreground[x] = malloc(GRID_Y * sizeof(char));*/
    /*}*/

    InitWindow(SCREEN_X, SCREEN_Y, "DO NOT LOSE FOCUS.x86");
    SetTargetFPS(60);

    setup_renderer();

    char** new_screen = generate_screen(0);
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            foreground[x][y] = new_screen[x][y];
        }
    }

    new_screen = generate_screen(0);
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            foreground[GRID_X + x][y] = new_screen[x][y];
        }
    }
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        scroll_level(1, foreground);
        
        if (should_generate_screen(foreground)) {
            new_screen = generate_screen(0);
            for (int x = 0; x < GRID_X; x++) {
                for (int y = 0; y < GRID_Y; y++) {
                    foreground[GRID_X + x][y] = new_screen[x][y];
                }
            }
        }

        draw_level_to_screen(foreground);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
