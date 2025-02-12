#pragma once
#include <raylib.h>
#include "defines.h"
#include "decorations.h"
#include "player.h"

static char screen[GRID_X][GRID_Y];

void setup_renderer();
void draw_char(char c, int x, int y);
void output_screen(Color fg_color, Color bg_color);
char** get_screen();

void draw_level(char foreground[GRID_X * 2][GRID_Y], char background_1[GRID_X * 2][GRID_Y], char background_2[GRID_X * 2][GRID_Y]);
void draw_particles(Particle particles[MAX_PARTICLES]);
void draw_player(Player* player);
