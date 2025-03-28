#pragma once
#include "defines.h"
#include <raylib.h>

typedef struct particle {
    Vector2 pos;
    Vector2 speed;
    Vector2 accel;
    char states[PARTICLE_STATES];
    int current_state;
    float state_period;
    float state_timer;
    char* group;
} Particle;

void add_rods(char layer[GRID_X_SIZE * 2][GRID_Y_SIZE], char chr);

void clear_particles(Particle particles[MAX_PARTICLES]);
void insert_new_particle(Vector2 pos,
                         Vector2 speed,
                         Vector2 accel,
                         char states[PARTICLE_STATES],
                         int current_state,
                         float state_period,
                         char* group,
                         Particle particles[MAX_PARTICLES]);

void update_particles(Particle particles[MAX_PARTICLES], float anim_shift_speed);
