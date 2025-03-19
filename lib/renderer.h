#pragma once
#include "defines.h"
#include "decorations.h"
#include "player.h"
#include <raylib.h>

extern char screen[GRID_X_SIZE][GRID_Y_SIZE];

void setup_renderer();
void draw_char(char c, int x, int y);
void output_screen(Color fg_color, Color bg_color);

void draw_level(char foreground[GRID_X_SIZE * 2][GRID_Y_SIZE], char background_1[GRID_X_SIZE * 2][GRID_Y_SIZE], char background_2[GRID_X_SIZE * 2][GRID_Y_SIZE]);
void draw_particles(Particle particles[MAX_PARTICLES]);
void draw_player(Player* player);

void draw_small_font_num(int score, int origin_x, int origin_y);
void draw_big_font(char* str, int origin_x, int origin_y, char texture_char);
void draw_icon(int* icon, int origin_x, int origin_y, int icon_size_x, int icon_size_y);

void draw_invul_frames(int iframes, int iframes_max);
void draw_stage_text(int stage, char texture_char);
