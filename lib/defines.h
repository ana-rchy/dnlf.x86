#pragma once
#include <stdlib.h>

#define FRAME_RATE 60
#define SCREEN_X 1024
#define SCREEN_Y 576
#define UNIT_X 8
#define UNIT_Y 12
#define GRID_X SCREEN_X / UNIT_X
#define GRID_Y SCREEN_Y / UNIT_Y

#define FULL_BLOCK '`'
#define UP_HALF 'a'
#define DOWN_HALF 'b'
#define LEFT_HALF 'c'
#define RIGHT_HALF 'd'
#define HORIZ_LINE 'e'
#define VERT_LINE 'f'
#define LEFT_T_LINE 'g'
#define RIGHT_T_LINE 'h'
#define UP_T_LINE 'i'
#define DOWN_T_LINE 'j'
#define PLUS_LINE 'k'
#define DITHER_1 'l'
#define DITHER_2 'm'
#define DITHER_3 'n'

#define BG_1_PARALLAX_DIVIDER 2.0
#define BG_2_PARALLAX_DIVIDER 3.0

// these are actually the default windows terminal colors but yeag
#define DNLF_WHITE (Color) { 242, 242, 242, 255 }
#define DNLF_BLACK (Color) { 12, 12, 12, 255 }
#define DNLF_BLUE (Color) { 0, 55, 218, 255 }
#define DNLF_GREEN (Color) { 19, 161, 14, 255 }
#define DNLF_CYAN (Color) { 58, 150, 221, 255 }
#define DNLF_RED (Color) { 197, 15, 31, 255 }
#define DNLF_PURPLE (Color) { 136, 23, 152, 255 }
#define DNLF_YELLOW (Color) { 193, 156, 0, 255 }
#define DNLF_LIGHT_GRAY (Color) { 204, 204, 204, 255 }
#define DNLF_DARK_GRAY (Color) { 118, 118, 118, 255 }
#define DNLF_BRIGHT_BLUE (Color) { 59, 120, 255, 255 }
#define DNLF_BRIGHT_GREEN (Color) { 22, 198, 12, 255 }
#define DNLF_BRIGHT_CYAN (Color) { 97, 214, 214, 255 }
#define DNLF_BRIGHT_RED (Color) { 231, 72, 86, 255 }
#define DNLF_BRIGHT_PURPLE (Color) { 180, 0, 158, 255 }
#define DNLF_BRIGHT_YELLOW (Color) { 249, 241, 165, 255 }

#define MAX_AIR_BLOCKS 6
#define MIN_AIR_BLOCK_SIZE 2
#define MAX_AIR_BLOCK_SIZE 8

#define MAX_EDGE_BLOCKS 16
#define MAX_TALL_EDGE_BLOCKS 4
#define MIN_SHORT_TALL_BLOCK_DIFFERENCE 15

#define MAX_STAGE 15
#define STAGE_TIME 20
#define SCROLL_SPEED_ACCELERATION 0.0001

#define MAX_PARTICLES 1024
#define PARTICLE_STATES 2

#define PLAYER_X 30
#define PLAYER_START_Y (float) GRID_Y / 2
#define PLAYER_Y_ACCEL 0.04

#define NUM_FONT_X 5
#define NUM_FONT_Y 5
#define STAGE_FONT_X 9
#define STAGE_FONT_Y 8

#define SCORE_X_POS 1
#define SCORE_Y_POS 1
#define INVUL_FRAMES_X_POS 1
#define INVUL_FRAMES_Y_POS GRID_Y - 1 - NUM_FONT_Y
#define STAGE_CHAR_X_POS GRID_X - 1 - STAGE_FONT_X
#define STAGE_CHAR_Y_POS GRID_Y - 1 - STAGE_FONT_Y
#define STAGE_TEXT_X_POS STAGE_CHAR_X_POS - STAGE_FONT_X*5 - 4 - 2
#define STAGE_TEXT_Y_POS STAGE_CHAR_Y_POS


#define min(a, b) ( (a < b) ? a : b )
#define max(a, b) ( (a > b) ? a : b )
#define clamp(val, min_val, max_val) ( max(min(val, max_val), min_val) )
#define rand_range(min, max) ( (rand() % (max - min + 1)) + min )
