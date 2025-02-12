#include "renderer.h"
#include "defines.h"
#include <stdio.h>
#include <string.h>

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
        }
    }
}

char** get_screen() {
    return (char**) screen;
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
        if (strcmp(particles[i].group, "") == 0) {
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
