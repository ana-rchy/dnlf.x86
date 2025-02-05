#include <stdio.h>
#include <raylib.h>
#include "lib/defines.h"
#include "lib/renderer.h"
#include "lib/level.h"

char foreground[GRID_X * 2][GRID_Y], background_1[GRID_X * 2][GRID_Y], background_2[GRID_X * 2][GRID_Y];
float fg_scroll_overflow, bg_1_scroll_overflow, bg_2_scroll_overflow = 0;
float scroll_speed = 1;

Color bg_color = DNLF_WHITE;
Color fg_color = DNLF_BLACK;

int main() {
    InitWindow(SCREEN_X, SCREEN_Y, "DO NOT LOSE FOCUS.x86");
    SetTargetFPS(60);

    setup_renderer();

    setup_layer(FULL_BLOCK, foreground);
    setup_layer(DITHER_1, background_1);
    setup_layer(DITHER_3, background_2);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(bg_color);

        extend_layer_if_needed(FULL_BLOCK, foreground);
        extend_layer_if_needed(DITHER_1, background_1);
        extend_layer_if_needed(DITHER_3, background_2);
        
        scroll_layer(scroll_speed, foreground, &fg_scroll_overflow);
        scroll_layer(scroll_speed / BG_1_PARALLAX_DIVIDER, background_1, &bg_1_scroll_overflow);
        scroll_layer(scroll_speed / BG_2_PARALLAX_DIVIDER, background_2, &bg_2_scroll_overflow);

        draw_level_to_screen(fg_color, bg_color, foreground, background_1, background_2);

        scroll_speed += SCROLL_SPEED_ACCELERATION;
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
