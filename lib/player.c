#include "player.h"
#include <raylib.h>

void reset_player(Player* player) {
    player->y_pos = PLAYER_START_Y;
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
    
    player->y_speed += player->y_accel;
    player->y_pos += player->y_speed;

    if (player->y_pos < 0 || player->y_pos >= (float) GRID_Y) {
        player->y_pos = clamp(player->y_pos, 0, (float) GRID_Y - 1);
        player->y_speed = 0;
    }

    // TODO: hit the level blocks and stuff
}
