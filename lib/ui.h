#pragma once
#include "defines.h"
#include <stdbool.h>

bool* int_to_num_font(int num);
bool* int_to_stage_font(int num);

static const bool NUM_FONT_0[NUM_FONT_Y][NUM_FONT_X] = {
    {1,1,1,1,1},
    {1,0,0,1,1},
    {1,0,1,0,1},
    {1,1,0,0,1},
    {1,1,1,1,1},
};

static const bool NUM_FONT_1[NUM_FONT_Y][NUM_FONT_X] = {
    {0,0,0,1,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
};

static const bool NUM_FONT_2[NUM_FONT_Y][NUM_FONT_X] = {
    {1,1,1,1,1},
    {0,0,0,0,1},
    {1,1,1,1,1},
    {1,0,0,0,0},
    {1,1,1,1,1},
};

static const bool NUM_FONT_3[NUM_FONT_Y][NUM_FONT_X] = {
    {1,1,1,1,1},
    {0,0,0,0,1},
    {1,1,1,1,1},
    {0,0,0,0,1},
    {1,1,1,1,1},
};

static const bool NUM_FONT_4[NUM_FONT_Y][NUM_FONT_X] = {
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
};

static const bool NUM_FONT_5[NUM_FONT_Y][NUM_FONT_X] = {
    {1,1,1,1,1},
    {1,0,0,0,0},
    {1,1,1,1,1},
    {0,0,0,0,1},
    {1,1,1,1,1},
};

static const bool NUM_FONT_6[NUM_FONT_Y][NUM_FONT_X] = {
    {1,1,1,1,1},
    {1,0,0,0,0},
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
};

static const bool NUM_FONT_7[NUM_FONT_Y][NUM_FONT_X] = {
    {1,1,1,1,1},
    {0,0,0,0,1},
    {0,0,1,1,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
};

static const bool NUM_FONT_8[NUM_FONT_Y][NUM_FONT_X] = {
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
};

static const bool NUM_FONT_9[NUM_FONT_Y][NUM_FONT_X] = {
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {0,0,0,0,1},
    {1,1,1,1,1},
};

static const bool NUM_FONT_SLASH[NUM_FONT_Y][NUM_FONT_X] = {
    {0,0,0,0,1},
    {0,0,0,1,0},
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,0,0,0,0},
};

static const bool STAGE_FONT_STAGE_TEXT[STAGE_FONT_Y][STAGE_FONT_X * 5 + 4] = {
    {0,1,1,1,1,1,1,1,0, 0, 1,1,1,1,1,1,1,1,1, 0, 0,1,1,1,1,1,1,1,0, 0, 0,1,1,1,1,1,1,1,0, 0, 1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,0,1,1, 0, 0,0,0,1,1,1,0,0,0, 0, 1,1,1,0,0,0,1,1,1, 0, 1,1,1,0,0,0,1,1,1, 0, 1,1,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,0,0,0, 0, 0,0,0,1,1,1,0,0,0, 0, 1,1,1,0,0,0,1,1,1, 0, 1,1,1,0,0,0,0,0,0, 0, 1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,0, 0, 0,0,0,1,1,1,0,0,0, 0, 1,1,1,1,1,1,1,1,1, 0, 1,1,1,0,1,1,1,1,1, 0, 1,1,1,1,1,1,1,0,0},
    {1,1,0,0,0,0,1,1,1, 0, 0,0,0,1,1,1,0,0,0, 0, 1,1,1,1,1,1,1,1,1, 0, 1,1,1,0,0,0,0,1,1, 0, 1,1,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1, 0, 0,0,0,1,1,1,0,0,0, 0, 1,1,1,0,0,0,1,1,1, 0, 1,1,1,1,1,1,1,1,1, 0, 1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,0, 0, 0,0,0,1,1,1,0,0,0, 0, 1,1,1,0,0,0,1,1,1, 0, 0,1,1,1,1,1,1,1,0, 0, 1,1,1,1,1,1,1,1,1},
};

static const bool STAGE_FONT_1[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,0,0,0},
    {1,1,1,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,0,0,0},
};

static const bool STAGE_FONT_2[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,1,1,1,0},
    {0,0,0,0,1,1,1,0,0},
    {0,0,0,1,1,1,0,0,0},
    {0,0,1,1,1,0,0,0,0},
    {0,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
};

static const bool STAGE_FONT_3[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {0,0,0,0,1,1,1,1,0},
    {0,0,0,0,1,1,1,1,0},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,0},
};

static const bool STAGE_FONT_4[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,0,0,0,1,1,0},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,1,1,0},
};

static const bool STAGE_FONT_5[STAGE_FONT_Y][STAGE_FONT_X] = {
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,0},
};

static const bool STAGE_FONT_6[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,0},
};

static const bool STAGE_FONT_7[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,1,1},
    {0,0,0,0,1,1,1,1,1},
    {0,0,0,0,1,1,1,1,1},
    {0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,1,1,0},
};

static const bool STAGE_FONT_8[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {0,1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,0},
};

static const bool STAGE_FONT_9[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,0},
};

static const bool STAGE_FONT_A[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
};

static const bool STAGE_FONT_B[STAGE_FONT_Y][STAGE_FONT_X] = {
    {1,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,0},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,0},
};

static const bool STAGE_FONT_C[STAGE_FONT_Y][STAGE_FONT_X] = {
    {0,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,0},
};

static const bool STAGE_FONT_D[STAGE_FONT_Y][STAGE_FONT_X] = {
    {1,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,0},
};

static const bool STAGE_FONT_E[STAGE_FONT_Y][STAGE_FONT_X] = {
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,0,0},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
};

static const bool STAGE_FONT_F[STAGE_FONT_Y][STAGE_FONT_X] = {
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,0,0},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0},
};
