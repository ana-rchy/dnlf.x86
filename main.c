#include "lib/defines.h"
#include "lib/renderer.h"
#include "lib/level.h"
#include "lib/decorations.h"
#include "lib/player.h"
#include "lib/ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

char foreground[GRID_X * 2][GRID_Y],
     background_1[GRID_X * 2][GRID_Y],
     background_2[GRID_X * 2][GRID_Y],
     ui[GRID_X][GRID_Y];
float fg_scroll_overflow, bg_1_scroll_overflow, bg_2_scroll_overflow = 0;

int stage = 0;
float timer = 0;
float scroll_speed = 1;

Color bg_color = DNLF_WHITE;
Color fg_color = DNLF_BLACK;

Particle particles[MAX_PARTICLES];

Player player = { GRID_Y / 2, 0, 0.04, 'v', 0, 15 };


void game_loop();
void level_loop();
void particles_loop();
void player_loop();

void set_stage_colors(int stage, Color* fg_color, Color* bg_color);


int main() {
    InitWindow(SCREEN_X, SCREEN_Y, "DO NOT LOSE FOCUS.x86");
    SetTargetFPS(60);
    setup_renderer();
    srand(time(NULL));

    setup_layer(foreground, FULL_BLOCK, player.invul_frames);
    setup_layer(background_1, DITHER_1, player.invul_frames);
    setup_layer(background_2, DITHER_3, player.invul_frames);

    clear_particles(particles);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(bg_color);

        game_loop();

        output_screen(fg_color, bg_color);
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void game_loop() {
    level_loop();

    draw_level(foreground, background_1, background_2);
    draw_particles(particles);
    draw_player(&player);
    draw_num_font((bool*) STAGE_FONT_STAGE_TEXT, STAGE_FONT_X * 5 + 4, 0, 0);

    // yes this order is VERY intentional
    // see: update_player comments and OG code ('game_loop()')
    particles_loop();
    update_player(&player, particles);

    timer += GetFrameTime();
    stage = min(timer / STAGE_TIME, MAX_STAGE);
    set_stage_colors(stage, &fg_color, &bg_color);
}

void level_loop() {
    scroll_and_extend_layer(foreground, stage, FULL_BLOCK, scroll_speed, &fg_scroll_overflow, player.invul_frames);
    scroll_and_extend_layer(background_1, stage, DITHER_1, scroll_speed / BG_1_PARALLAX_DIVIDER, &bg_1_scroll_overflow, player.invul_frames);
    scroll_and_extend_layer(background_2, stage, DITHER_3, scroll_speed / BG_2_PARALLAX_DIVIDER, &bg_2_scroll_overflow, player.invul_frames);

    scroll_speed += SCROLL_SPEED_ACCELERATION;
}

void particles_loop() {
    update_particles(particles);

    insert_new_particle(
        (Vector2) { PLAYER_X, player.y },
        (Vector2) { -scroll_speed, 0 },
        (Vector2) { 0, 0 },
        (char[PARTICLE_STATES]) { '+', '-' },
        0,
        10.0 / 60.0,
        "player trail",
        particles
    );

    if (rand_range(1, 10) == 1) {
        insert_new_particle(
            (Vector2) { (float) GRID_X - 1, rand_range(0, GRID_Y - 1) },
            (Vector2) { -scroll_speed * rand_range(2, 4), 0 },
            (Vector2) { 0, 0 },
            (char[PARTICLE_STATES]) { '-', '*' },
            0,
            rand_range(1, 10) / 60.0,
            "fly-by",
            particles
        );
    }
}

//////////////////////////////////////////////////////////////////

void set_stage_colors(int stage, Color* fg_color, Color* bg_color) {
    switch (stage) {
    case 1:
        *fg_color = DNLF_BLUE;
        break;

    case 2:
        *fg_color = DNLF_GREEN;
        break;

    case 3:
        *fg_color = DNLF_CYAN;
        break;

    case 4:
        *fg_color = DNLF_RED;
        break;

    case 5:
        *fg_color = DNLF_PURPLE;
        break;

    case 6:
        *fg_color = DNLF_YELLOW;
        break;

    case 7:
        *fg_color = DNLF_LIGHT_GRAY;
        break;

    case 8:
        *bg_color = DNLF_BLACK;
        *fg_color = DNLF_DARK_GRAY;
        break;

    case 9:
        *bg_color = DNLF_BLUE;
        *fg_color = DNLF_BRIGHT_BLUE;
        break;

    case 10:
        *bg_color = DNLF_GREEN;
        *fg_color = DNLF_BRIGHT_GREEN;
        break;

    case 11:
        *bg_color = DNLF_CYAN;
        *fg_color = DNLF_BRIGHT_CYAN;
        break;

    case 12:
        *bg_color = DNLF_RED;
        *fg_color = DNLF_BRIGHT_RED;
        break;

    case 13:
        *bg_color = DNLF_PURPLE;
        *fg_color = DNLF_BRIGHT_PURPLE;
        break;

    case 14:
        *bg_color = DNLF_YELLOW;
        *fg_color = DNLF_BRIGHT_YELLOW;
        break;

    case 15:
        *bg_color = DNLF_LIGHT_GRAY;
        *fg_color = DNLF_WHITE;
        break;
    }
}
