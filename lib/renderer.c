#include "renderer.h"
#include "defines.h"
#include "font.h"
#include <stdio.h>
#include <string.h>

// we need this for Special Physics (see: update_player)
char screen[GRID_X_SIZE][GRID_Y_SIZE];
Font font;

void setup_renderer() {
    font = LoadFont("font.png");
}

void draw_char(char c, int x, int y) {
    if (x < 0 || x >= GRID_X_SIZE || y < 0 || y >= GRID_Y_SIZE) {
        printf("char %c out of bounds @ (%d, %d)\n", c, x, y);
        return;
    }

    screen[x][y] = c;
}

void output_screen(Color fg_color, Color bg_color) {
    for (int x = 0; x < GRID_X_SIZE; x++) {
        for (int y = 0; y < GRID_Y_SIZE; y++) {
            Vector2 pos = { x * UNIT_X_SIZE, y * UNIT_Y_SIZE };

            // guarantee a string with a single char in it,
            // in an array it might be interpreted differently
            char chr[2];
            sprintf(chr, "%c", screen[x][y]);
            
            DrawRectangle(pos.x, pos.y, UNIT_X_SIZE, UNIT_Y_SIZE, bg_color);
            DrawTextEx(font, chr, pos, 12, 0, fg_color);

            screen[x][y] = ' ';
        }
    }
}

//////////////////////////////////////////////////////////////////

void draw_level(char foreground[GRID_X_SIZE * 2][GRID_Y_SIZE], char background_1[GRID_X_SIZE * 2][GRID_Y_SIZE], char background_2[GRID_X_SIZE * 2][GRID_Y_SIZE]) {
    for (int x = 0; x < GRID_X_SIZE; x++) {
        for (int y = 0; y < GRID_Y_SIZE; y++) {
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
    if (player->y_accel < 0) {
        draw_char('^', PLAYER_X_POS - 1, player->y);
    } else {
        draw_char('v', PLAYER_X_POS - 1, player->y);
    }

    if (player->invul_frames > 0) {
        draw_char('@', PLAYER_X_POS, player->y);
    } else {
        draw_char('#', PLAYER_X_POS, player->y);
    }
}

//////////////////////////////////////////////////////////////////

void draw_small_font(char* str, int origin_x, int origin_y, char texture_char) {
    int str_len = strlen(str);

    for (int i = 0; i < str_len; i++) {
        if (str[i] == ' ') {
            origin_x++;
            continue;
        }

        bool* font_char = char_to_small_font(str[i]);
        
        for (int y = 0; y < SMALL_FONT_Y_SIZE; y++) {
            for (int x = 0; x < SMALL_FONT_X_SIZE; x++) {
                if ( *(font_char + y*SMALL_FONT_X_SIZE + x) == true ) {
                    draw_char(texture_char, origin_x + x, origin_y + y);
                }
            }
        }

        origin_x += SMALL_FONT_X_SIZE + 1;
    }
}

void draw_big_font(char* str, int origin_x, int origin_y, char texture_char) {
    int str_len = strlen(str);

    for (int i = 0; i < str_len; i++) {
        if (str[i] == ' ') {
            origin_x++;
            continue;
        }

        bool* font_char = char_to_big_font(str[i]);
        
        for (int y = 0; y < BIG_FONT_Y_SIZE; y++) {
            for (int x = 0; x < BIG_FONT_X_SIZE; x++) {
                if ( *(font_char + y*BIG_FONT_X_SIZE + x) == true ) {
                    draw_char(texture_char, origin_x + x, origin_y + y);
                }
            }
        }

        origin_x += BIG_FONT_X_SIZE + 1;
    }
}

void draw_icon(int* icon, int origin_x, int origin_y, int icon_size_x, int icon_size_y) {
    for (int y = 0; y < icon_size_y; y++) {
        for (int x = 0; x < icon_size_x; x++) {
            int texture_char = texture_int_to_char( *(icon + y*icon_size_x + x) );

            if (texture_char != ' ') {
                draw_char(texture_char, origin_x + x, origin_y + y);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////

void draw_score(int score) {
    if (score > 0) {
        char buffer[50];
        snprintf(buffer, 50, "%d", score);

        draw_small_font(buffer, SCORE_X_POS, SCORE_Y_POS, DITHER_2);
    }
}

void draw_invul_frames(int iframes, int iframes_max) {
    if (iframes < 0) {
        printf("draw_invul_frames: iframes less than 0");
        return;
    }
   
    // compiler complains if this is only 6 bytes, so its 24 bytes
    char buffer[24];
    snprintf(buffer, 24, "%02d/%02d", iframes, iframes_max);

    draw_small_font(buffer, INVUL_FRAMES_X_POS, INVUL_FRAMES_Y_POS, DITHER_2);
}

void draw_stage_text(int stage, char texture_char) {
    char buffer[8];

    snprintf(buffer, 8, "STAGE %c", stage_int_to_char(stage));

    draw_big_font(buffer, STAGE_TEXT_X_POS, STAGE_TEXT_Y_POS, texture_char);
}
