#include "game.h"
#include "defines.h"
#include "font.h"
#include "layer.h"
#include "payloads/text_files.h"
#include "renderer.h"
#include "level.h"
#include "decorations.h"
#include "player.h"
#include "stage.h"
#include <math.h>
#include <raylib.h>


GameState game_state = Menu;
bool run_menu_init = true;
bool run_ingame_init = true;
bool run_death_init = true;
bool run_loading_init = true;
bool run_exiting_init = true;
bool run_won_init = true;

char foreground[GRID_X_SIZE * 2][GRID_Y_SIZE],
     background_1[GRID_X_SIZE * 2][GRID_Y_SIZE],
     background_2[GRID_X_SIZE * 2][GRID_Y_SIZE],
     animation_layer[GRID_X_SIZE * 2][GRID_Y_SIZE];
float fg_scroll_overflow, bg_1_scroll_overflow, bg_2_scroll_overflow, animation_shift_overflow = 0;

int stage = 0;
float time_since_game_start = 0;

float scroll_speed = 1;
float total_distance = 0;

// idk why it starts at 1 man the og just does that
float animation_shift_distance = 1;

Color bg_color = DNLF_WHITE;
Color fg_color = DNLF_BLACK;

Particle particles[MAX_PARTICLES];
Player player = {};

Music current_audio;
Music menu_music;
Music ingame_music;
Music death_sfx;


//=================================================================================================================//


void game_init() {
    menu_music = LoadMusicStream("assets/menumusic.wav");
    ingame_music = LoadMusicStream("assets/losingfocusv1.wav");
    death_sfx = LoadMusicStream("assets/death.wav");
    
    death_sfx.looping = false;

    write_and_open_howtoplay_if_nonexistant();
}

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
            if (run_ingame_init) {
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

        case Won:
            if (run_won_init) {
                won_init();
            }

            won_loop();
            break;
    }

    UpdateMusicStream(current_audio);

    if (!IsWindowState(FLAG_WINDOW_HIDDEN)) {
        draw_and_flush_screen(fg_color, bg_color);
    }
}

void game_exit() {
    UnloadMusicStream(menu_music);
    UnloadMusicStream(ingame_music);
    CloseAudioDevice();
    CloseWindow();
    exit(0);
}


//=================================================================================================================//


// BUG: we dont reset the color here because in the og it doesnt either :^)
void menu_init() {
    run_menu_init = false;
    run_loading_init = true;
    run_exiting_init = true;

    clear_particles(particles);

    // audio
    StopMusicStream(current_audio);
    current_audio = menu_music;
    PlayMusicStream(current_audio);
}

void menu_loop() {
    draw_particles(particles);

    draw_big_font("DO          NOT", MENU_DO_NOT_X_POS, MENU_DO_NOT_Y_POS, FULL_BLOCK);
    draw_big_font("LOSE          FOCUS", MENU_LOSE_FOCUS_X_POS, MENU_LOSE_FOCUS_Y_POS, FULL_BLOCK);

    draw_icon((int*) ICON_PLAY_ARROW, MENU_PLAY_ARROW_X_POS, MENU_PLAY_ARROW_Y_POS, ICON_PLAY_ARROW_X_SIZE, ICON_PLAY_ARROW_Y_SIZE);
    draw_icon((int*) ICON_EXIT_DOOR, MENU_EXIT_DOOR_X_POS, MENU_EXIT_DOOR_Y_POS, ICON_EXIT_DOOR_X_SIZE, ICON_EXIT_DOOR_Y_SIZE);

    // particles
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

    update_particles(particles, 0);


    // screen buttons / state transitions
    Rectangle play_arrow_rect = {
        MENU_PLAY_ARROW_X_POS * UNIT_X_SIZE,
        MENU_PLAY_ARROW_Y_POS * UNIT_Y_SIZE,
        ICON_PLAY_ARROW_X_SIZE * UNIT_X_SIZE,
        ICON_PLAY_ARROW_Y_SIZE * UNIT_Y_SIZE,
    };

    Rectangle exit_door_rect = {
        MENU_EXIT_DOOR_X_POS * UNIT_X_SIZE,
        MENU_EXIT_DOOR_Y_POS * UNIT_Y_SIZE,
        ICON_EXIT_DOOR_X_SIZE * UNIT_X_SIZE,
        ICON_EXIT_DOOR_Y_SIZE * UNIT_Y_SIZE,
    };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), play_arrow_rect)) {
        game_state = Loading;
    }

    if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), exit_door_rect)) ||
        IsKeyPressed(KEY_ESCAPE))
    {
        game_state = Exiting;
    }
}


//=================================================================================================================//


// yoink the main `screen` with no particles and just text/icons, onto the anim layer
// then do it again for the loading text, onto the future part of the anim layer
// a bit cursed but it works
void loading_init() {
    run_loading_init = false;
    run_ingame_init = true;
    animation_shift_distance = 1;


    // current screen to layer
    draw_big_font("DO          NOT", MENU_DO_NOT_X_POS, MENU_DO_NOT_Y_POS, FULL_BLOCK);
    draw_big_font("LOSE          FOCUS", MENU_LOSE_FOCUS_X_POS, MENU_LOSE_FOCUS_Y_POS, FULL_BLOCK);
    draw_icon((int*) ICON_PLAY_ARROW, MENU_PLAY_ARROW_X_POS, MENU_PLAY_ARROW_Y_POS, ICON_PLAY_ARROW_X_SIZE, ICON_PLAY_ARROW_Y_SIZE);
    draw_icon((int*) ICON_EXIT_DOOR, MENU_EXIT_DOOR_X_POS, MENU_EXIT_DOOR_Y_POS, ICON_EXIT_DOOR_X_SIZE, ICON_EXIT_DOOR_Y_SIZE);

    move_2d_array_screen_to_layer(animation_layer, screen, false);
    flush_screen();


    // future screen to layer
    draw_big_font("LOADING", LOADING_X_POS, LOADING_Y_POS, FULL_BLOCK);
    draw_icon((int*) ICON_HOURGLASS, LOADING_HOURGLASS_X_POS, LOADING_HOURGLASS_Y_POS, ICON_HOURGLASS_X_SIZE, ICON_HOURGLASS_Y_SIZE);

    move_2d_array_screen_to_layer(animation_layer, screen, true);
    flush_screen();
}

void loading_loop() {
    draw_particles(particles);
    draw_layer(animation_layer);


    // animation layer shifting
    float prev_anim_shift_dist = animation_shift_distance == 1 ? 0 : animation_shift_distance;

    if (animation_shift_distance > 0) {
        animation_shift_distance += ((float) GRID_X_SIZE - animation_shift_distance) / 10;
    }

    float anim_shift_speed = animation_shift_distance - prev_anim_shift_dist;
    animation_shift_overflow += fmod(anim_shift_speed, 1);

    if (animation_shift_overflow >= 1) {
        anim_shift_speed += (int) animation_shift_overflow;
        animation_shift_overflow = fmod(animation_shift_overflow, 1);
    }

    shift_layer_left_by(anim_shift_speed, animation_layer);


    // particles
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

    update_particles(particles, animation_shift_distance);

    
    // state transitions
    if (animation_shift_distance + 0.01 >= (float) GRID_X_SIZE) {
        game_state = Ingame;
    }
}

// essentially the same as loading_init()
void exiting_init() {
    run_exiting_init = false;
    animation_shift_distance = 1;


    // current screen to layer
    draw_big_font("DO          NOT", MENU_DO_NOT_X_POS, MENU_DO_NOT_Y_POS, FULL_BLOCK);
    draw_big_font("LOSE          FOCUS", MENU_LOSE_FOCUS_X_POS, MENU_LOSE_FOCUS_Y_POS, FULL_BLOCK);
    draw_icon((int*) ICON_PLAY_ARROW, MENU_PLAY_ARROW_X_POS, MENU_PLAY_ARROW_Y_POS, ICON_PLAY_ARROW_X_SIZE, ICON_PLAY_ARROW_Y_SIZE);
    draw_icon((int*) ICON_EXIT_DOOR, MENU_EXIT_DOOR_X_POS, MENU_EXIT_DOOR_Y_POS, ICON_EXIT_DOOR_X_SIZE, ICON_EXIT_DOOR_Y_SIZE);

    move_2d_array_screen_to_layer(animation_layer, screen, false);
    flush_screen();


    // future screen to layer
    draw_big_font("THANKS          FOR", EXITING_THANKS_FOR_X_POS, EXITING_THANKS_FOR_Y_POS, FULL_BLOCK);
    draw_big_font("PLAYING", EXITING_PLAYING_X_POS, EXITING_PLAYING_Y_POS, FULL_BLOCK);
    draw_icon((int*) ICON_EXCLAMATION, EXITING_EXCLAMATION_X_POS, EXITING_EXCLAMATION_Y_POS, ICON_EXCLAMATION_X_SIZE, ICON_EXCLAMATION_Y_SIZE);
    draw_icon((int*) ICON_HEART, EXITING_HEART_X_POS, EXITING_HEART_Y_POS, ICON_HEART_X_SIZE, ICON_HEART_Y_SIZE);

    move_2d_array_screen_to_layer(animation_layer, screen, true);
    flush_screen();
}

void exiting_loop() {
    draw_particles(particles);
    draw_layer(animation_layer);


    // animation layer shifting
    float prev_anim_shift_dist = animation_shift_distance == 1 ? 0 : animation_shift_distance;

    if (animation_shift_distance > 0) {
        animation_shift_distance += ((float) GRID_X_SIZE - animation_shift_distance) / 10;
    }

    float anim_shift_speed = animation_shift_distance - prev_anim_shift_dist;
    animation_shift_overflow += fmod(anim_shift_speed, 1);

    if (animation_shift_overflow >= 1) {
        anim_shift_speed += (int) animation_shift_overflow;
        animation_shift_overflow = fmod(animation_shift_overflow, 1);
    }

    shift_layer_left_by(anim_shift_speed, animation_layer);


    // particles
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

    update_particles(particles, animation_shift_distance);


    // state transitions
    if (animation_shift_distance + 0.01 >= (float) GRID_X_SIZE) {
        game_exit();
    }
}


//=================================================================================================================//


void ingame_init() {
    // various game variables being reset
    run_ingame_init = false;
    run_death_init = true;
    run_menu_init = true;

    fg_scroll_overflow = bg_1_scroll_overflow = bg_2_scroll_overflow = 0;

    stage = 0;
    time_since_game_start = 0;

    scroll_speed = 1;
    total_distance = 0;

    bg_color = DNLF_WHITE;
    fg_color = DNLF_BLACK;


    // and various resetting functions
    setup_foreground(foreground);
    setup_layer(background_1, DITHER_1);
    setup_layer(background_2, DITHER_3);

    reset_player(&player);

    clear_particles(particles);

    // audio
    StopMusicStream(current_audio);
    current_audio = ingame_music;
    PlayMusicStream(current_audio);
}

void ingame_loop() {
    time_since_game_start += GetFrameTime();

    draw_layer(background_2);
    draw_layer(background_1);
    draw_layer(foreground);

    draw_particles(particles);
    draw_player(&player);

    draw_invul_frames(player.invul_frames, player.invul_frames_max);
    draw_score(player.score);


    // yes this order is VERY intentional
    // see: update_player comments and OG code ('game_loop()')
    ingame_level_loop();
    ingame_stage_loop();
    ingame_particles_loop();


    // state transitions
    if (update_player(&player, particles, total_distance)) {
        game_state = Dead;
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        game_state = Menu;
    }

    if (time_since_game_start >= STAGE_TIME * (MAX_STAGE + 1)) {
        game_state = Won;
    }
}

void won_init() {
    SetWindowState(FLAG_WINDOW_HIDDEN);

}

void won_loop() {
    time_since_game_start += GetFrameTime();

    if (time_since_game_start >= GetMusicTimeLength(current_audio)) {
        write_and_open_credits_if_nonexistant();
        game_exit();
    }
}


//=================================================================================================================//


void ingame_level_loop() {
    total_distance += scroll_speed;
    scroll_speed += SCROLL_SPEED_ACCELERATION;

    shift_left_and_extend_layer(foreground, stage, FULL_BLOCK, scroll_speed, &fg_scroll_overflow, player.invul_frames);
    shift_left_and_extend_layer(background_1, stage, DITHER_1, scroll_speed / BG_1_PARALLAX_DIVIDER, &bg_1_scroll_overflow, player.invul_frames);
    shift_left_and_extend_layer(background_2, stage, DITHER_3, scroll_speed / BG_2_PARALLAX_DIVIDER, &bg_2_scroll_overflow, player.invul_frames);
}

void ingame_particles_loop() {
    update_particles(particles, 0);

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


//=================================================================================================================//


void death_init() {
    run_death_init = false;
    run_ingame_init = true;
    run_menu_init = true;

    // particles
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

    // audio
    StopMusicStream(current_audio);
    current_audio = death_sfx;
    PlayMusicStream(current_audio);
}

void death_loop() {
    draw_layer(background_2);
    draw_layer(background_1);
    draw_layer(foreground);

    draw_particles(particles);

    draw_invul_frames(player.invul_frames, player.invul_frames_max);
    draw_score(player.score);

    draw_big_font("GAME OVER", GAME_OVER_X_POS, GAME_OVER_Y_POS, DITHER_2);


    update_particles(particles, 0);


    // state transitions
    if (IsKeyPressed(KEY_SPACE)) {
        game_state = Ingame;
    } else if (IsKeyPressed(KEY_ESCAPE)) {
        game_state = Menu;
    }
}
