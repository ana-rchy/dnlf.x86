#pragma once

typedef enum GameState {
    Menu,
    Ingame,
    Dead,
} GameState;

void game_loop();

void menu_init();
void menu_loop();

void ingame_init();
void ingame_loop();

void ingame_level_loop();
void ingame_particles_loop();
void ingame_stage_loop();

void death_init();
void death_loop();
