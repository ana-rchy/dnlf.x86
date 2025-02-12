#pragma once

typedef struct Player {
    float y_pos;
    float y_speed;
    float y_accel;
    char head_char;
    int invul_frames;
    int invul_frames_max;
} Player;

void reset_player(Player* player);
void update_player(Player* player);
