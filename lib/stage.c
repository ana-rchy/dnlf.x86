#include "stage.h"
#include "defines.h"

void set_stage_colors(int stage, Color* fg_color, Color* bg_color) {
    switch (stage) {
    case 1:
        *fg_color = DNLF_BLUE;
        break;

    case 2:
        *fg_color = DNLF_GREEN;
        break;

    case 3:
        *fg_color = DNLF_CYAN;
        break;

    case 4:
        *fg_color = DNLF_RED;
        break;

    case 5:
        *fg_color = DNLF_PURPLE;
        break;

    case 6:
        *fg_color = DNLF_YELLOW;
        break;

    case 7:
        *fg_color = DNLF_LIGHT_GRAY;
        break;

    case 8:
        *bg_color = DNLF_BLACK;
        *fg_color = DNLF_DARK_GRAY;
        break;

    case 9:
        *bg_color = DNLF_BLUE;
        *fg_color = DNLF_BRIGHT_BLUE;
        break;

    case 10:
        *bg_color = DNLF_GREEN;
        *fg_color = DNLF_BRIGHT_GREEN;
        break;

    case 11:
        *bg_color = DNLF_CYAN;
        *fg_color = DNLF_BRIGHT_CYAN;
        break;

    case 12:
        *bg_color = DNLF_RED;
        *fg_color = DNLF_BRIGHT_RED;
        break;

    case 13:
        *bg_color = DNLF_PURPLE;
        *fg_color = DNLF_BRIGHT_PURPLE;
        break;

    case 14:
        *bg_color = DNLF_YELLOW;
        *fg_color = DNLF_BRIGHT_YELLOW;
        break;

    case 15:
        *bg_color = DNLF_LIGHT_GRAY;
        *fg_color = DNLF_WHITE;
        break;
    }
}
