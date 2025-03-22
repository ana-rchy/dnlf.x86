#include "lib/defines.h"
#include "lib/game.h"
#include "lib/renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

int main() {
    InitWindow(SCREEN_X_SIZE, SCREEN_Y_SIZE, "DO NOT LOSE FOCUS.x86");
    SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
    SetTargetFPS(60);
    SetExitKey(-1); // no key... i think
    InitAudioDevice();

    setup_terminal_font();

    srand(time(NULL));

    game_init();

    while (!WindowShouldClose()) {
        BeginDrawing();
        
        game_loop();

        EndDrawing();
    }

    game_exit();
    return 0;
}
