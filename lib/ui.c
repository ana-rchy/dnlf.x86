#include "ui.h"
#include <stdio.h>

bool* int_to_num_font(int num) {
    switch (num) {
    case 0:
        return (bool*) NUM_FONT_0;

    case 1:
        return (bool*) NUM_FONT_1;

    case 2:
        return (bool*) NUM_FONT_2;

    case 3:
        return (bool*) NUM_FONT_3;

    case 4:
        return (bool*) NUM_FONT_4;

    case 5:
        return (bool*) NUM_FONT_5;

    case 6:
        return (bool*) NUM_FONT_6;

    case 7:
        return (bool*) NUM_FONT_7;

    case 8:
        return (bool*) NUM_FONT_8;

    case 9:
        return (bool*) NUM_FONT_9;

    default:
        printf("int_to_num_font: invalid int for num font, %d\n", num);
        return (bool*) NUM_FONT_0;

    }
}
