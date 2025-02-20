#pragma once

typedef enum GameState {
    Menu,
    Ingame,
    Dead,
} GameState;

void game_loop();

void menu_loop();

void ingame_init();
void ingame_loop();

void death_init();
void death_loop();

void level_loop();
void particles_loop();
void stage_loop();
