#include "game.h"
#include "defines.h"
#include "renderer.h"
#include "level.h"
#include "decorations.h"
#include "player.h"
#include "stage.h"
#include <math.h>
#include <raylib.h>


GameState game_state = Ingame;
bool run_game_init = true;
bool run_death_init = true;

char foreground[GRID_X * 2][GRID_Y],
     background_1[GRID_X * 2][GRID_Y],
     background_2[GRID_X * 2][GRID_Y],
     ui[GRID_X][GRID_Y];
float fg_scroll_overflow, bg_1_scroll_overflow, bg_2_scroll_overflow = 0;

int stage = 0;
float time_since_game_start = 0;

float scroll_speed = 1;
float total_distance = 0;

Color bg_color = DNLF_WHITE;
Color fg_color = DNLF_BLACK;

Particle particles[MAX_PARTICLES];
Player player = {};

//////////////////////////////////////////////////////////////////

void game_loop() {
    ClearBackground(bg_color);
        
    switch (game_state) {
    case Menu:
        break;

    case Ingame:
        if (run_game_init) {
            ingame_init();
        }

        ingame_loop();
        break;

    case Dead:
         if (run_death_init) {
            death_init();
        }

        death_loop();
        break;
    }

    output_screen(fg_color, bg_color);
}

//////////////////////////////////////////////////////////////////

void ingame_init() {
    run_death_init = true;

    fg_scroll_overflow = bg_1_scroll_overflow = bg_2_scroll_overflow = 0;

    stage = 0;
    time_since_game_start = 0;

    scroll_speed = 1;
    total_distance = 0;

    bg_color = DNLF_WHITE;
    fg_color = DNLF_BLACK;

    setup_foreground(foreground);
    setup_layer(background_1, DITHER_1);
    setup_layer(background_2, DITHER_3);

    reset_player(&player);

    clear_particles(particles);
}

void ingame_loop() {
    run_game_init = false;

    draw_level(foreground, background_1, background_2);
    draw_particles(particles);
    draw_player(&player);
    draw_invul_frames(player.invul_frames, player.invul_frames_max);
    if (player.score > 0) {
        draw_ui_num(player.score, SCORE_X_POS, SCORE_Y_POS);
    }

    level_loop();
    stage_loop();

    // yes this order is VERY intentional
    // see: update_player comments and OG code ('game_loop()')
    particles_loop();
    update_player(&player, particles, total_distance, &game_state);
}

//////////////////////////////////////////////////////////////////

void death_init() {
    run_game_init = true;

    for (int i = 0; i < 20; i++) {
        insert_new_particle(
            (Vector2) { PLAYER_X, player.y },
            (Vector2) {
                (float) rand_range(-30, 30) / 20,
                (float) rand_range(-30, 30) / 20
            },
            (Vector2) { 0, PLAYER_Y_ACCEL },
            (char[PARTICLE_STATES]) { '|', '-' },
            0,
            3,
            "death",
            particles
        );
    }

    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (TextIsEqual(particles[i].group, "player trail")) {
            particles[i].speed = (Vector2) {
                (float) rand_range(-30, 0) / 20,
                (float) rand_range(-30, 30) / 20
            };
        }
    }
}

void death_loop() {
    run_death_init = false;

    draw_level(foreground, background_1, background_2);
    draw_particles(particles);
    draw_invul_frames(player.invul_frames, player.invul_frames_max);
    if (player.score > 0) {
        draw_ui_num(player.score, SCORE_X_POS, SCORE_Y_POS);
    }

    update_particles(particles);

    if (IsKeyPressed(KEY_SPACE)) {
        game_state = Ingame;
    }
}

//////////////////////////////////////////////////////////////////

void level_loop() {
    total_distance += scroll_speed;
    scroll_speed += SCROLL_SPEED_ACCELERATION;

    scroll_and_extend_layer(foreground, stage, FULL_BLOCK, scroll_speed, &fg_scroll_overflow, player.invul_frames);
    scroll_and_extend_layer(background_1, stage, DITHER_1, scroll_speed / BG_1_PARALLAX_DIVIDER, &bg_1_scroll_overflow, player.invul_frames);
    scroll_and_extend_layer(background_2, stage, DITHER_3, scroll_speed / BG_2_PARALLAX_DIVIDER, &bg_2_scroll_overflow, player.invul_frames);
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

void stage_loop() {
    time_since_game_start += GetFrameTime();
    stage = min(time_since_game_start / STAGE_TIME, MAX_STAGE);

    set_stage_colors(stage, &fg_color, &bg_color);
    set_invul_frames_max(stage, &player.invul_frames_max);
    
    float time_since_current_stage = time_since_game_start - stage*STAGE_TIME;

    if (time_since_current_stage <= STAGE_TEXT_VISIBLE_TIME && stage > 0) {
        if (fmod(time_since_current_stage, STAGE_TEXT_CHAR_PERIOD) < STAGE_TEXT_CHAR_PERIOD / 2) {
            draw_stage_text(stage, FULL_BLOCK);
        } else {
            draw_stage_text(stage, DITHER_2);
        }
    }

    if (time_since_current_stage < 1.0 / 60.0 && stage > 0) {
        player.score += 2500;
        player.invul_frames = min(player.invul_frames + 10, player.invul_frames_max);
    }
}
