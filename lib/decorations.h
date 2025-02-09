#pragma once
#include <raylib.h>
#include "defines.h"

typedef struct particle {
    Vector2 pos;
    Vector2 speed;
    Vector2 accel;
    char states[2];
    int current_state;
    float state_period;
    float state_timer;
    char* group;
} Particle;

void add_rods(char layer[GRID_X * 2][GRID_Y], char chr);

void clear_particles(Particle particles[MAX_PARTICLES]);
void insert_new_particle(Vector2 pos, Vector2 speed, Vector2 accel, char states[2], int current_state, float state_period, char* group, Particle particles[MAX_PARTICLES]);
void update_particles(Particle particles[MAX_PARTICLES]);
