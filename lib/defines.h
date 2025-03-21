#pragma once
#include <stdlib.h>

//// window ////
#define FRAME_RATE 60
#define SCREEN_X_SIZE 1024
#define SCREEN_Y_SIZE 576
#define UNIT_X_SIZE 8
#define UNIT_Y_SIZE 12
#define GRID_X_SIZE SCREEN_X_SIZE / UNIT_X_SIZE
#define GRID_Y_SIZE SCREEN_Y_SIZE / UNIT_Y_SIZE

//// font chars ////
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

//// font sizes ////
#define SMALL_FONT_X_SIZE 5
#define SMALL_FONT_Y_SIZE 5
#define BIG_FONT_X_SIZE 9
#define BIG_FONT_Y_SIZE 8

#define ICON_PLAY_ARROW_X_SIZE BIG_FONT_X_SIZE
#define ICON_PLAY_ARROW_Y_SIZE BIG_FONT_Y_SIZE
#define ICON_EXIT_DOOR_X_SIZE BIG_FONT_X_SIZE
#define ICON_EXIT_DOOR_Y_SIZE BIG_FONT_Y_SIZE
#define ICON_HOURGLASS_X_SIZE BIG_FONT_X_SIZE
#define ICON_HOURGLASS_Y_SIZE BIG_FONT_Y_SIZE
#define ICON_EXCLAMATION_X_SIZE 3
#define ICON_EXCLAMATION_Y_SIZE BIG_FONT_Y_SIZE
#define ICON_HEART_X_SIZE 10
#define ICON_HEART_Y_SIZE BIG_FONT_Y_SIZE

//// font etc ////
// menu
#define MENU_DO_NOT_X_POS 16
#define MENU_DO_NOT_Y_POS 11
#define MENU_PLAY_ARROW_X_POS MENU_DO_NOT_X_POS
#define MENU_PLAY_ARROW_Y_POS (MENU_DO_NOT_Y_POS + 9)
#define MENU_LOSE_FOCUS_X_POS MENU_DO_NOT_X_POS
#define MENU_LOSE_FOCUS_Y_POS (MENU_PLAY_ARROW_Y_POS + 9)
#define MENU_EXIT_DOOR_X_POS (MENU_PLAY_ARROW_X_POS + 50)
#define MENU_EXIT_DOOR_Y_POS MENU_PLAY_ARROW_Y_POS

// loading/exiting
// NOTE: it looks like the x pos is 11 in the og when the loading anim stops moving,
// BUT the text actually only moves 127 units, not 128 units
// which means that the text is actually x pos 10 originally on the future screen
// ...this shit took me 12 hours to figure out
#define LOADING_X_POS (11 - 1)
#define LOADING_Y_POS 20
#define LOADING_HOURGLASS_X_POS (LOADING_X_POS + 71)
#define LOADING_HOURGLASS_Y_POS LOADING_Y_POS

#define EXITING_THANKS_FOR_X_POS LOADING_X_POS
#define EXITING_THANKS_FOR_Y_POS 15
#define EXITING_PLAYING_X_POS EXITING_THANKS_FOR_X_POS
#define EXITING_PLAYING_Y_POS (EXITING_THANKS_FOR_Y_POS + 10)
#define EXITING_EXCLAMATION_X_POS (EXITING_PLAYING_X_POS + 70)
#define EXITING_EXCLAMATION_Y_POS EXITING_PLAYING_Y_POS
#define EXITING_HEART_X_POS (EXITING_EXCLAMATION_X_POS + 5)
#define EXITING_HEART_Y_POS EXITING_EXCLAMATION_Y_POS

// ingame
#define SCORE_X_POS 1
#define SCORE_Y_POS 1
#define INVUL_FRAMES_X_POS 1
#define INVUL_FRAMES_Y_POS (GRID_Y_SIZE - 1 - SMALL_FONT_Y_SIZE)
#define STAGE_CHAR_X_POS (GRID_X_SIZE - 1 - BIG_FONT_X_SIZE)
#define STAGE_CHAR_Y_POS (GRID_Y_SIZE - 1 - BIG_FONT_Y_SIZE)
#define STAGE_TEXT_X_POS (STAGE_CHAR_X_POS - BIG_FONT_X_SIZE*5 - 4 - 2)
#define STAGE_TEXT_Y_POS STAGE_CHAR_Y_POS

// game over
#define GAME_OVER_X_POS 24
#define GAME_OVER_Y_POS 20
#define GAME_OVER_TEXTURE_CHAR DITHER_2

//// colors ////
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

//// background ////
#define BG_1_PARALLAX_DIVIDER 2.0
#define BG_2_PARALLAX_DIVIDER 3.0

//// level gen ////
#define MAX_AIR_BLOCKS 6
#define MAX_EDGE_BLOCKS 16

#define MIN_AIR_BLOCK_SIZE 2
#define MAX_AIR_BLOCK_SIZE 8

#define MAX_TALL_EDGE_BLOCKS 4
#define MIN_SHORT_TALL_BLOCK_DIFFERENCE 15

//// stage ////
#define MAX_STAGE 15
#define STAGE_TIME 20

#define STAGE_TEXT_VISIBLE_TIME (30.0 / 60.0)
#define STAGE_TEXT_CHAR_PERIOD (2.0 / 30.0)

//// particles ////
#define MAX_PARTICLES 1024
#define PARTICLE_STATES 2

//// player ////
#define PLAYER_X_POS 30
#define PLAYER_START_Y_POS ((float) GRID_Y_SIZE / 2)
#define PLAYER_Y_ACCEL 0.04

#define SCROLL_SPEED_ACCELERATION 0.0001



//// macros ////
#define min(a, b) ( (a < b) ? a : b )
#define max(a, b) ( (a > b) ? a : b )
#define clamp(val, min_val, max_val) ( max(min(val, max_val), min_val) )
#define rand_range(min, max) ( (rand() % (max - min + 1)) + min )
