#include "renderer.h"
#include "defines.h"
#include "ui.h"
#include <raylib.h>
#include <stdio.h>
#include <math.h>

// we need this for Special Physics (see: update_player)
char screen[GRID_X][GRID_Y];
Font font;

void setup_renderer() {
    font = LoadFont("font.png");
}

void draw_char(char c, int x, int y) {
    if (x < 0 || x >= GRID_X || y < 0 || y >= GRID_Y) {
        printf("char %c out of bounds @ (%d, %d)\n", c, x, y);
        return;
    }

    screen[x][y] = c;
}

void output_screen(Color fg_color, Color bg_color) {
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            Vector2 pos = { x * UNIT_X, y * UNIT_Y };

            // guarantee a string with a single char in it,
            // in an array it might be interpreted differently
            char chr[2];
            sprintf(chr, "%c", screen[x][y]);
            
            DrawRectangle(pos.x, pos.y, UNIT_X, UNIT_Y, bg_color);
            DrawTextEx(font, chr, pos, 12, 0, fg_color);

            screen[x][y] = ' ';
        }
    }
}

//////////////////////////////////////////////////////////////////

void draw_level(char foreground[GRID_X * 2][GRID_Y], char background_1[GRID_X * 2][GRID_Y], char background_2[GRID_X * 2][GRID_Y]) {
    for (int x = 0; x < GRID_X; x++) {
        for (int y = 0; y < GRID_Y; y++) {
            draw_char(background_2[x][y], x, y);

            if (background_1[x][y] != ' ') {
                draw_char(background_1[x][y], x, y);
            }

            if (foreground[x][y] != ' ') {
                draw_char(foreground[x][y], x, y);
            }
       }
    }
}

void draw_particles(Particle particles[MAX_PARTICLES]) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (TextIsEqual(particles[i].group, "")) {
            continue;
        }

        char chr = particles[i].states[particles[i].current_state];

        draw_char(chr, (int) particles[i].pos.x, (int) particles[i].pos.y);
    }
}

void draw_player(Player* player) {
    draw_char(player->head_char, PLAYER_X - 1, player->y);

    if (player->invul_frames > 0) {
        draw_char('@', PLAYER_X, player->y);
    } else {
        draw_char('#', PLAYER_X, player->y);
    }
}

void draw_ui_num(int num, int origin_x, int origin_y) {
    int digits_count;
    if (num > 0) {
        digits_count = (int) log10(num) + 1;
    } else {
        digits_count = 1;
    }

    int start_x = origin_x + 6*(digits_count - 1);

    for (int i = 1; i <= digits_count; i++) {
        bool* font_char = int_to_num_font(num % 10);

        for (int y = 0; y < NUM_FONT_Y; y++) {
            for (int x = 0; x < NUM_FONT_X; x++) {
                if ( *(font_char + y*NUM_FONT_X + x) == true ) {
                    draw_char(DITHER_2, start_x + x, origin_y + y);
                }
            }
        }

        start_x -= 6;
        num /= 10;
    }
}

void draw_invul_frames(int iframes, int iframes_max) {
    if (iframes < 0) {
        printf("draw_invul_frames: iframes less than 0");
        return;
    }

    if (iframes >= 10) {
        draw_ui_num(iframes, INVUL_FRAMES_X_POS, INVUL_FRAMES_Y_POS);
    } else {
        draw_ui_num(0, INVUL_FRAMES_X_POS, INVUL_FRAMES_Y_POS);
        draw_ui_num(iframes, INVUL_FRAMES_X_POS + 6, INVUL_FRAMES_Y_POS);
    }

    for (int y = 0; y < NUM_FONT_Y; y++) {
        for (int x = 0; x < NUM_FONT_X; x++) {
            if (NUM_FONT_SLASH[y][x] == true) {
                draw_char(DITHER_2, INVUL_FRAMES_X_POS + 6*2 + x, INVUL_FRAMES_Y_POS + y);
            }
        }
    }

    draw_ui_num(iframes_max, INVUL_FRAMES_X_POS + 6*3, INVUL_FRAMES_Y_POS);
}
