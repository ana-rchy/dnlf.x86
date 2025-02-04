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

#define max(a,b) ( ((a) > (b)) ? (a) : (b) )
