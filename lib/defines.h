#pragma once

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
#define T_LINE 'g'
#define UPSDWN_T_LINE 'h'
#define PLUS_LINE 'i'
#define DITHER_1 'j'
#define DITHER_2 'k'
#define DITHER_3 'l'

#define DNLF_WHITE (Color) { 242, 242, 242, 255 }

#define MAX_AIR_BLOCKS 6
#define MIN_AIR_BLOCK_SIZE 2
#define MAX_AIR_BLOCK_SIZE 8

#define MAX_EDGE_BLOCKS 16
#define MAX_TALL_EDGE_BLOCKS 4
#define MIN_SHORT_TALL_BLOCK_DIFFERENCE 15

#define SCROLL_SPEED_ACCELERATION 0.0001

#define max(a,b) ( ((a) > (b)) ? (a) : (b) )
