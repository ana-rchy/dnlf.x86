#include "player.h"
#include "decorations.h"
#include "defines.h"
#include "renderer.h"
#include <raylib.h>
#include <stdio.h>

void reset_player(Player* player) {
    player->y = PLAYER_START_Y;
    player->y_speed = 0;
    player->y_accel = PLAYER_Y_ACCEL;
    // in OG, char is set to 'v' only on init, not on reset
    player->invul_frames = 0;
    player->invul_frames_max = 15;
}

// there is some wacky stuff that went down in the OG's version of this
//
// so: in the OG, it checked physics on the *display* layer
// in physics() (player physics) it would draw particles if you were *about* to hit a wall
//
// draw_frame() would push particles onto the display layer
// and in the game loop, draw_frame() ran before physics()
//
// without considering iframes or death, the player just gets snapped to the nearest wall/ceiling (see next comment)
// so the only reason the player can go into walls in the OG,
// is because the particles override where the player is about to be on the display layer,
// and the physics checking from that layer, dont see FULL_BLOCK and are like "yep thats all good"
//
// as i am making this a 100% authentic port, this exact behaviour will be here too.
// Too bad!
void update_player(Player* player, Particle particles[MAX_PARTICLES]) {
    char in_front = screen[PLAYER_X + 1][(int) player->y];

    if (in_front >= FULL_BLOCK && in_front <= RIGHT_HALF) {
        for (int i = 0; i < 3; i++) {
            insert_new_particle(
                (Vector2) { PLAYER_X - 1, player->y },
                (Vector2) { 
                    (float) rand_range(-30, -1) / 20.0,
                    (float) rand_range(-30, 30) / 20.0
                },
                (Vector2) { 0, PLAYER_Y_ACCEL },
                (char[PARTICLE_STATES]) { DITHER_2, DITHER_1 },
                0, // OG '1-2*rand()%2' always == 1, convert 1/-1 to 0/1, we get 0
                3.0 / 60.0,
                "invuln",
                particles
            );
        }
    }
    
    if (IsKeyPressed(KEY_UP)) {
        player->y_accel = -player->y_accel;
        player->y_speed = player->y_speed / 2;

        player->head_char = player->head_char == 'v' ? '^' : 'v';
    }
    
    if (player->y_accel < 0) {
        if (player->y > 0 && screen[PLAYER_X][(int) player->y - 1] != FULL_BLOCK) {
            player->y_speed += player->y_accel;
        } else {
            player->y_speed = 0;
        }
    } else if (player->y_accel > 0) {
        if (player->y < (float) GRID_Y - 1 && screen[PLAYER_X][(int) player->y + 1] != FULL_BLOCK) {
            player->y_speed += player->y_accel;
        } else {
            player->y_speed = 0;
        }
    }

    player->y += player->y_speed;

    float push_direction = (player->y < (float) GRID_Y / 2) ? 1 : -1;

    // OG only checks for FULL_BLOCK, so we also do the same,
    // this of course is a bug. Too bad!
    //
    // overall this while loop causes the player to be pushed down/upwards until theres air, depending on push_direction
    while (screen[PLAYER_X][(int) player->y] == FULL_BLOCK ||
           player->y < 0 || player->y >= (float) GRID_Y)
    {
        player->y += push_direction;
        player->y_speed = 0;
    }
}
