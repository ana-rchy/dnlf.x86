#pragma once
#include <raylib.h>
#include "defines.h"
#include "decorations.h"
#include "player.h"

void setup_renderer();
void draw_char(char c, int x, int y, Color fg_color, Color bg_color);
void draw_level_to_screen(Color fg_color, Color bg_color, char foreground[GRID_X * 2][GRID_Y], char background_1[GRID_X * 2][GRID_Y], char background_2[GRID_X * 2][GRID_Y]);
void draw_particles(Color fg_color, Color bg_color, Particle particles[MAX_PARTICLES]);
void draw_player(Color fg_color, Color bg_color, Player* player);
