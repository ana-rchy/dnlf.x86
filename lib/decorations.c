#include "decorations.h"
#include "defines.h"
#include <raylib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// TODO: make this function more readable jfc
void add_rods(char layer[GRID_X * 2][GRID_Y], char chr) {
    for (int x = GRID_X; x < GRID_X * 2; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            if (rand_range(1, 64) != 1) {
                continue;
            }

            int rod_direction = -1;
            
            // bias towards vertical rods cause it checks for walls up and down for vertical,
            // but only to the left for horizontal
            if (layer[x][y] == ' ') {
                // - 1 for length to index, - 1 to be not on the edge
                if (y <= GRID_Y - 2 && layer[x][y + 1] == chr) {
                    rod_direction = 1;
                }
                if (x >= GRID_X + 1 && layer[x - 1][y] == chr) {
                    rod_direction = 2;
                }
                if (y >= 1 && layer[x][y - 1] == chr) {
                    rod_direction = 3;
                }
            }

            switch (rod_direction) {
            case 1:
                for (int y2 = y; y2 >= 0 && layer[x][y2] != chr; y2--) {
                    layer[x][y2] = VERT_LINE;
                }
                break;

            case 2:
                for (int x2 = x; x2 < GRID_X * 2 && layer[x2][y] != chr; x2++) {
                    if (rand_range(1, 10) == 1) {
                        layer[x2][y] = DOWN_T_LINE;
                    } else {
                        layer[x2][y] = HORIZ_LINE;
                    }
                }
                break;

            case 3:
                for (int y2 = y; y2 < GRID_Y && layer[x][y2] != chr; y2++) {
                    layer[x][y2] = VERT_LINE;
                }
                break;
            }
        }
    }

    for (int y = 0; y < GRID_Y; y++) {
        // this should actually check if it could be a T too,
        // but we preserving all the bugs here so, Too bad!
        if (layer[GRID_X - 1][y] == HORIZ_LINE && layer[GRID_X][y] == ' ') {
            for (int x = GRID_X; x < GRID_X * 2 && layer[x][y] != chr; x++) {
                layer[x][y] = HORIZ_LINE;
            }
        }
    }

    for (int x = GRID_X; x < GRID_X * 2; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            bool leftwards = (x >= GRID_X + 1 && layer[x - 1][y] == HORIZ_LINE);

            bool rightwards = (x <= (GRID_X*2) - 2 && layer[x + 1][y] == HORIZ_LINE);

            bool upwards = (y >= 1 && layer[x][y - 1] == VERT_LINE);

            bool downwards = (y <= GRID_Y - 2 && layer[x][y + 1] == VERT_LINE);

            if (leftwards && rightwards && upwards && downwards) {
                layer[x][y] = PLUS_LINE;
            } else if (leftwards && upwards && downwards) {
                layer[x][y] = LEFT_T_LINE;
            } else if (rightwards && upwards && downwards) {
                layer[x][y] = RIGHT_T_LINE;
            } else if (leftwards && rightwards && upwards) {
                layer[x][y] = UP_T_LINE;
            } else if (leftwards && rightwards && downwards) {
                layer[x][y] = DOWN_T_LINE;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////

void clear_particles(Particle particles[MAX_PARTICLES]) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].group = "";
    }
}

void insert_new_particle(Vector2 pos,
                         Vector2 speed,
                         Vector2 accel,
                         char states[PARTICLE_STATES],
                         int current_state,
                         float state_period,
                         char* group,
                         Particle particles[MAX_PARTICLES])
{
    int free_index = -1;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (strcmp(particles[i].group, "") == 0) {
            free_index = i;
            break;
        }
    }

    if (free_index == -1) {
        return;
    }

    particles[free_index].pos = pos;
    particles[free_index].speed = speed;
    particles[free_index].accel = accel;
    particles[free_index].states[0] = states[0];
    particles[free_index].states[1] = states[1];
    particles[free_index].current_state = current_state;
    particles[free_index].state_period = state_period;
    particles[free_index].group = group;
}

//////////////////////////////////////////////////////////////////

void update_particles(Particle particles[MAX_PARTICLES]) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (strcmp(particles[i].group, "") == 0) {
            continue;
        }

        particles[i].speed.x += particles[i].accel.x;
        particles[i].speed.y += particles[i].accel.y;

        // TODO: og is 'part[i].x += part[i].dx + part[i].dx * (xlen-shifta)/20*(shifta>1);'
        // the 'shifta' part speeds up the particles on the main menu once play is pressed, together with the rest of the screen
        particles[i].pos.x += particles[i].speed.x;
        particles[i].pos.y += particles[i].speed.y;

        if (particles[i].pos.x < 0 || particles[i].pos.x >= (float) GRID_X ||
            particles[i].pos.y < 0 || particles[i].pos.y >= (float) GRID_Y)
        {
            particles[i].group = "";
            return;
        }

        particles[i].state_timer += GetFrameTime();

        if (particles[i].state_period != -1 && particles[i].state_timer >= particles[i].state_period) {
            particles[i].current_state = (particles[i].current_state + 1) % PARTICLE_STATES;
            particles[i].state_timer -= particles[i].state_period;
        }
    }
}
