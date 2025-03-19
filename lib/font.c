#include "font.h"
#include "defines.h"
#include <stdio.h>

bool* char_to_small_font(char c) {
    switch (c) {
        case '0':
            return (bool*) SMALL_FONT_0;

        case '1':
            return (bool*) SMALL_FONT_1;

        case '2':
            return (bool*) SMALL_FONT_2;

        case '3':
            return (bool*) SMALL_FONT_3;

        case '4':
            return (bool*) SMALL_FONT_4;

        case '5':
            return (bool*) SMALL_FONT_5;

        case '6':
            return (bool*) SMALL_FONT_6;

        case '7':
            return (bool*) SMALL_FONT_7;

        case '8':
            return (bool*) SMALL_FONT_8;

        case '9':
            return (bool*) SMALL_FONT_9;

        case '/':
            return (bool*) SMALL_FONT_SLASH;

        default:
            printf("char_to_small_font: invalid char for small font, %c\n", c);
            return (bool*) SMALL_FONT_0;
    }
}

//////////////////////////////////////////////////////////////////

char stage_int_to_char(int num) {
    if (num < 1 || num > 15) {
        printf("int_to_big_font: invalid int for big font, %d\n", num);
        return '0';
    }

    char buffer[2];
    snprintf(buffer, 2, "%X", num);

    return buffer[0];
}


bool* char_to_big_font(char c) {
    switch (c) {
        case '1':
            return (bool*) BIG_FONT_1;

        case '2':
            return (bool*) BIG_FONT_2;

        case '3':
            return (bool*) BIG_FONT_3;

        case '4':
            return (bool*) BIG_FONT_4;

        case '5':
            return (bool*) BIG_FONT_5;

        case '6':
            return (bool*) BIG_FONT_6;

        case '7':
            return (bool*) BIG_FONT_7;

        case '8':
            return (bool*) BIG_FONT_8;

        case '9':
            return (bool*) BIG_FONT_9;

        case 'A':
            return (bool*) BIG_FONT_A;

        case 'B':
            return (bool*) BIG_FONT_B;

        case 'C':
            return (bool*) BIG_FONT_C;

        case 'D':
            return (bool*) BIG_FONT_D;

        case 'E':
            return (bool*) BIG_FONT_E;

        case 'F':
            return (bool*) BIG_FONT_F;

        case 'G':
            return (bool*) BIG_FONT_G;

        case 'H':
            return (bool*) BIG_FONT_H;

        case 'I':
            return (bool*) BIG_FONT_I;

        // no J

        case 'K':
            return (bool*) BIG_FONT_K;

        case 'L':
            return (bool*) BIG_FONT_L;

        case 'M':
            return (bool*) BIG_FONT_M;

        case 'N':
            return (bool*) BIG_FONT_N;

        case 'O':
            return (bool*) BIG_FONT_O;

        case 'P':
            return (bool*) BIG_FONT_P;

        // no Q
        
        case 'R':
            return (bool*) BIG_FONT_R;

        case 'S':
            return (bool*) BIG_FONT_S;

        case 'T':
            return (bool*) BIG_FONT_T;

        case 'U':
            return (bool*) BIG_FONT_U;

        case 'V':
            return (bool*) BIG_FONT_V;

        // no W, X

        case 'Y':
            return (bool*) BIG_FONT_Y;

        // no Z
        
        default:
            printf("char_to_big_font: invalid char for big font, %c\n", c);
            return (bool*) BIG_FONT_A;
    }
}

//////////////////////////////////////////////////////////////////

char texture_int_to_char(int num) {
    if (num == 0) {
        return ' ';
    }

    if (num < 1 || num > 5) {
        printf("texture_int_to_char: invalid num, %d\n", num);
        return ' ';
    }

    return FULL_BLOCK + (num - 1);
}
