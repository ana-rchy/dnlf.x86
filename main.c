#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "lib/defines.h"
#include "lib/renderer.h"
#include "lib/level.h"
#include "lib/decorations.h"

char foreground[GRID_X * 2][GRID_Y], background_1[GRID_X * 2][GRID_Y], background_2[GRID_X * 2][GRID_Y];
float fg_scroll_overflow, bg_1_scroll_overflow, bg_2_scroll_overflow = 0;

Particle particles[MAX_PARTICLES];

float scroll_speed = 1;

Color bg_color = DNLF_WHITE;
Color fg_color = DNLF_BLACK;

void game_loop();
void level_loop();
void particles_loop();

int main() {
    InitWindow(SCREEN_X, SCREEN_Y, "DO NOT LOSE FOCUS.x86");
    SetTargetFPS(60);
    setup_renderer();
    srand(time(NULL));

    setup_layer(FULL_BLOCK, foreground);
    setup_layer(DITHER_1, background_1);
    setup_layer(DITHER_3, background_2);

    clear_particles(particles);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(bg_color);

        game_loop();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void game_loop() {
    level_loop();
    particles_loop();
}

void level_loop() {
    scroll_and_extend_layer(foreground, FULL_BLOCK, scroll_speed, &fg_scroll_overflow);
    scroll_and_extend_layer(background_1, DITHER_1, scroll_speed / BG_1_PARALLAX_DIVIDER, &bg_1_scroll_overflow);
    scroll_and_extend_layer(background_2, DITHER_3, scroll_speed / BG_2_PARALLAX_DIVIDER, &bg_2_scroll_overflow);

    scroll_speed += SCROLL_SPEED_ACCELERATION;

    draw_level_to_screen(fg_color, bg_color, foreground, background_1, background_2);
}

void particles_loop() {
    update_particles(particles);

    if (rand_range(1, 10) == 1) {
        insert_new_particle(
            (Vector2) { (float) GRID_X - 1, rand_range(0, GRID_Y - 1) },
            (Vector2) { -scroll_speed * rand_range(2, 4), 0 },
            (Vector2) { 0, 0 },
            (char[PARTICLE_STATES]) { '*', '-' },
            0,
            rand_range(1, 10) / 60.0,
            "fly-by",
            particles
        );
    }

    draw_particles(fg_color, bg_color, particles);
}
