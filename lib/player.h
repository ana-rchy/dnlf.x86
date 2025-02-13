#pragma once
#include "defines.h"
#include "decorations.h"

typedef struct Player {
    float y;
    float y_speed;
    float y_accel;
    char head_char;
    int invul_frames;
    int invul_frames_max;
} Player;

void reset_player(Player* player);
void update_player(Player* player, Particle particles[MAX_PARTICLES]);
