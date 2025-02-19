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
    player->score = 0;
}

// BUG:
// in the OG, it checked physics on the *display* layer
// specifically, the while loop checks what is on the players position on the screen
// on the screen this is *usually* the player head char, '#' or '@'
// this bug is what allows you to break through walls, as it sees #/@ rather than FULL_BLOCK
// sometimes it doesnt see #/@ and then you move up/down a little while in a wall
// ...also, particles can affect physics.
// Too bad!
void update_player(Player* player, Particle particles[MAX_PARTICLES], float total_distance, int stage) {
    char in_front = screen[PLAYER_X + 1][(int) player->y];

    if (in_front >= FULL_BLOCK && in_front <= RIGHT_HALF) {
        if (player->invul_frames == 0) {

        } else {
            player->invul_frames--;

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
    }
    
    if (IsKeyPressed(KEY_UP)) {
        player->y_accel = -player->y_accel;
        player->y_speed = player->y_speed / 2;
    }
    
    if (player->y_accel < 0) {
        if (player->y > 0 && screen[PLAYER_X][(int) player->y - 1] != FULL_BLOCK) {
            player->y_speed += player->y_accel;
        } else {
            player->y_speed = 0;

            if (total_distance > 48) {
                player->score += 10;

                if (player->score % 250 == 0) {
                    player->invul_frames = min(player->invul_frames + 1, player->invul_frames_max);
                }
            }
        }
    } else if (player->y_accel > 0) {
        if (player->y < (float) GRID_Y - 1 && screen[PLAYER_X][(int) player->y + 1] != FULL_BLOCK) {
            player->y_speed += player->y_accel;
        } else {
            player->y_speed = 0;

            if (total_distance > 48) {
                player->score += 10;
                
                // NOTE:
                // in the OG, it had this be only from stage 7 onwards,
                // and % 125 afterwards
                // but you only ever gain minimum 10 points. so,
                // 125 is redundant and is the same as % 250
                // Too bad!
                if (player->score % 250 == 0) {
                    player->invul_frames = min(player->invul_frames + 1, player->invul_frames_max);
                }
            }
        }
    }

    player->y += player->y_speed;

    float push_direction = (player->y < (float) GRID_Y / 2) ? 1 : -1;

    // BUG:
    // OG only checks for FULL_BLOCK, so we do the same
    // Too bad!
    while (screen[PLAYER_X][(int) player->y] == FULL_BLOCK ||
           player->y < 0 || player->y >= (float) GRID_Y)
    {
        player->y += push_direction;
        player->y_speed = 0;
    }
}
