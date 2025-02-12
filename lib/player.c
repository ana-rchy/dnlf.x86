#include "player.h"
#include "defines.h"
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

void update_player(Player* player, char foreground[GRID_X * 2][GRID_Y]) {
    if (IsKeyPressed(KEY_UP)) {
        player->y_accel = -player->y_accel;
        player->y_speed = player->y_speed / 2;

        player->head_char = player->head_char == 'v' ? '^' : 'v';
    }

    if (player->y_accel < 0) {
        if (player->y > 0 && foreground[PLAYER_X][(int) player->y - 1] != FULL_BLOCK) {
            player->y_speed += player->y_accel;
        } else {
            player->y_speed = 0;
        }
    }

    if (player->y_accel > 0) {
        if (player->y < (float) GRID_Y - 1 && foreground[PLAYER_X][(int) player->y + 1] != FULL_BLOCK) {
            player->y_speed += player->y_accel;
        } else {
            player->y_speed = 0;
        }
    }

    player->y += player->y_speed;

    if (player->y >= GRID_Y / 2)
        while (foreground[PLAYER_X][(int) player->y] == FULL_BLOCK || player->y >= GRID_Y) {
            player->y--;
            player->y_speed = 0;
        }

    if (player->y < GRID_Y / 2)
        while (foreground[PLAYER_X][(int) player->y] == FULL_BLOCK || player->y < 0) {
            player->y++;
            player->y_speed = 0;
        }
    
    /*player->y_speed += player->y_accel;*/
    /*player->y_pos += player->y_speed;*/
    /**/
    /*float push_direction = (player->y_pos < (float) GRID_Y / 2) ? 1 : -1;*/
    /**/
    /*// OG only checks for FULL_BLOCK, so we also do the same,*/
    /*// this of course is a bug. Too bad!*/
    /*//*/
    /*// overall this while loop causes the player to be pushed down/upwards until theres air, depending on push_direction*/
    /*while (foreground[PLAYER_X][(int) player->y_pos] == FULL_BLOCK ||*/
    /*       player->y_pos < 0 || player->y_pos >= (float) GRID_Y)*/
    /*{*/
    /*    player->y_pos += push_direction;*/
    /*    player->y_speed = 0;*/
    /*}*/
}
