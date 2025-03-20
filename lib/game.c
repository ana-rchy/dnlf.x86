#include "game.h"
#include "defines.h"
#include "font.h"
#include "layer.h"
#include "renderer.h"
#include "level.h"
#include "decorations.h"
#include "player.h"
#include "stage.h"
#include <math.h>
#include <raylib.h>


GameState game_state = Menu;
bool run_menu_init = true;
bool run_game_init = true;
bool run_death_init = true;
bool run_loading_init = true;
bool run_exiting_init = true;

char foreground[GRID_X_SIZE * 2][GRID_Y_SIZE],
     background_1[GRID_X_SIZE * 2][GRID_Y_SIZE],
     background_2[GRID_X_SIZE * 2][GRID_Y_SIZE],
     animation_layer[GRID_X_SIZE * 2][GRID_Y_SIZE];
float fg_scroll_overflow, bg_1_scroll_overflow, bg_2_scroll_overflow, animation_shift_overflow = 0;

int stage = 0;
float time_since_game_start = 0;

float scroll_speed = 1;
float total_distance = 0;

float animation_shift_distance = 1;

Color bg_color = DNLF_WHITE;
Color fg_color = DNLF_BLACK;

Particle particles[MAX_PARTICLES];
Player player = {};

//////////////////////////////////////////////////////////////////

void game_loop() {
    ClearBackground(bg_color);
        
    switch (game_state) {
        case Menu:
            if (run_menu_init) {
                menu_init();
            }

            menu_loop();
            break;

        case Loading:
            if (run_loading_init) {
                loading_init();
            }

            loading_loop();
            break;

        case Exiting:
            if (run_exiting_init) {
                exiting_init();
            }

            exiting_loop();
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

    draw_and_flush_screen(fg_color, bg_color);
}

//////////////////////////////////////////////////////////////////

void menu_init() {
    run_menu_init = false;

    clear_particles(particles);
}

void menu_loop() {
    draw_particles(particles);

    draw_big_font("DO          NOT", MENU_DO_NOT_X_POS, MENU_DO_NOT_Y_POS, FULL_BLOCK);
    draw_big_font("LOSE          FOCUS", MENU_LOSE_FOCUS_X_POS, MENU_LOSE_FOCUS_Y_POS, FULL_BLOCK);

    draw_icon((int*) ICON_PLAY_ARROW, MENU_PLAY_ARROW_X_POS, MENU_PLAY_ARROW_Y_POS, ICON_PLAY_ARROW_X_SIZE, ICON_PLAY_ARROW_Y_SIZE);
    draw_icon((int*) ICON_EXIT_DOOR, MENU_EXIT_DOOR_X_POS, MENU_EXIT_DOOR_Y_POS, ICON_EXIT_DOOR_X_SIZE, ICON_EXIT_DOOR_Y_SIZE);

    if (rand_range(0, 1) == 1) {
        insert_new_particle(
            (Vector2) { (float) GRID_X_SIZE - 1, rand_range(0, GRID_Y_SIZE - 1) },
            (Vector2) { ((float) rand_range(-29, 0) / 10) - 1, 0 },
            (Vector2) { 0, 0 },
            (char[PARTICLE_STATES]) { '*', '*' },
            0,
            -1,
            "fly-by",
            particles
        );
    }

    update_particles(particles);

    if (IsKeyPressed(KEY_SPACE)) {
        game_state = Loading;
    }
}

//////////////////////////////////////////////////////////////////

// yoink the main `screen` with no particles and just text/icons, onto the anim layer
// then do it again for the loading text, onto the future part of the anim layer
// a bit cursed but it works
void loading_init() {
    run_loading_init = false;

    draw_big_font("DO          NOT", MENU_DO_NOT_X_POS, MENU_DO_NOT_Y_POS, FULL_BLOCK);
    draw_big_font("LOSE          FOCUS", MENU_LOSE_FOCUS_X_POS, MENU_LOSE_FOCUS_Y_POS, FULL_BLOCK);
    draw_icon((int*) ICON_PLAY_ARROW, MENU_PLAY_ARROW_X_POS, MENU_PLAY_ARROW_Y_POS, ICON_PLAY_ARROW_X_SIZE, ICON_PLAY_ARROW_Y_SIZE);
    draw_icon((int*) ICON_EXIT_DOOR, MENU_EXIT_DOOR_X_POS, MENU_EXIT_DOOR_Y_POS, ICON_EXIT_DOOR_X_SIZE, ICON_EXIT_DOOR_Y_SIZE);

    move_2d_array_screen_to_layer(animation_layer, screen, false);
    flush_screen();

    draw_big_font("LOADING", LOADING_X_POS, LOADING_Y_POS, FULL_BLOCK);
    draw_icon((int*) ICON_HOURGLASS, LOADING_HOURGLASS_X_POS, LOADING_HOURGLASS_Y_POS, ICON_HOURGLASS_X_SIZE, ICON_HOURGLASS_Y_SIZE);

    move_2d_array_screen_to_layer(animation_layer, screen, true);
    flush_screen();
}

void loading_loop() {
    draw_particles(particles);
    draw_layer(animation_layer);


    float prev_anim_shift_dist = animation_shift_distance == 1 ? 0 : animation_shift_distance;

    if (animation_shift_distance > 0) {
        animation_shift_distance += ((float) GRID_X_SIZE - animation_shift_distance) / 10;
    }

    if (animation_shift_distance + 0.01 >= (float) GRID_X_SIZE) {
        animation_shift_distance = 0;
    }

    float anim_shift_speed = animation_shift_distance - prev_anim_shift_dist;

    animation_shift_overflow += fmod(anim_shift_speed, 1);

    if (animation_shift_overflow >= 1) {
        anim_shift_speed += (int) animation_shift_overflow;
        animation_shift_overflow = fmod(animation_shift_overflow, 1);
    }


    shift_layer_left_by(anim_shift_speed, animation_layer);


    if (rand_range(0, 1) == 1) {
        insert_new_particle(
            (Vector2) { (float) GRID_X_SIZE - 1, rand_range(0, GRID_Y_SIZE - 1) },
            (Vector2) { ((float) rand_range(-29, 0) / 10) - 1, 0 },
            (Vector2) { 0, 0 },
            (char[PARTICLE_STATES]) { '*', '*' },
            0,
            -1,
            "fly-by",
            particles
        );
    }

    update_particles(particles);
}

// same as loading_init()
void exiting_init() {
    run_exiting_init = false;
}

void exiting_loop() {

}

//////////////////////////////////////////////////////////////////

void ingame_init() {
    run_game_init = false;
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
    draw_layer(background_2);
    draw_layer(background_1);
    draw_layer(foreground);

    draw_particles(particles);
    draw_player(&player);

    draw_invul_frames(player.invul_frames, player.invul_frames_max);
    draw_score(player.score);

    ingame_level_loop();
    ingame_stage_loop();

    // yes this order is VERY intentional
    // see: update_player comments and OG code ('game_loop()')
    ingame_particles_loop();
    update_player(&player, particles, total_distance, &game_state);
}

//////////////////////////////////////////////////////////////////

void ingame_level_loop() {
    total_distance += scroll_speed;
    scroll_speed += SCROLL_SPEED_ACCELERATION;

    shift_left_and_extend_layer(foreground, stage, FULL_BLOCK, scroll_speed, &fg_scroll_overflow, player.invul_frames);
    shift_left_and_extend_layer(background_1, stage, DITHER_1, scroll_speed / BG_1_PARALLAX_DIVIDER, &bg_1_scroll_overflow, player.invul_frames);
    shift_left_and_extend_layer(background_2, stage, DITHER_3, scroll_speed / BG_2_PARALLAX_DIVIDER, &bg_2_scroll_overflow, player.invul_frames);
}

void ingame_particles_loop() {
    update_particles(particles);

    insert_new_particle(
        (Vector2) { PLAYER_X_POS, player.y },
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
            (Vector2) { (float) GRID_X_SIZE - 1, rand_range(0, GRID_Y_SIZE - 1) },
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

void ingame_stage_loop() {
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

//////////////////////////////////////////////////////////////////

void death_init() {
    run_death_init = false;
    run_game_init = true;

    for (int i = 0; i < 20; i++) {
        insert_new_particle(
            (Vector2) { PLAYER_X_POS, player.y },
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
    draw_layer(background_2);
    draw_layer(background_1);
    draw_layer(foreground);

    draw_particles(particles);

    draw_invul_frames(player.invul_frames, player.invul_frames_max);
    draw_score(player.score);

    draw_big_font("GAME OVER", GAME_OVER_X_POS, GAME_OVER_Y_POS, DITHER_2);

    update_particles(particles);

    if (IsKeyPressed(KEY_SPACE)) {
        game_state = Ingame;
    }
}
