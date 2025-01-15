#include "level.h"
#include "defines.h"
#include "renderer.h"

char level[SCREEN_TEXT_X * 2][SCREEN_TEXT_Y];

void setup_level() {
    for (int x = 0; x < SCREEN_TEXT_X; x++) {
        for (int y = 0; y < SCREEN_TEXT_Y; y++) {
            level[x][y] = T_LINE;
            draw_char(level[x][y], x, y);
        }
    }
}
