#include "lib/defines.h"
#include "lib/game.h"
#include "lib/renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

int main() {
    InitWindow(SCREEN_X_SIZE, SCREEN_Y_SIZE, "DO NOT LOSE FOCUS.x86");
    SetTargetFPS(60);
    SetExitKey(-1); // no key... i think

    setup_terminal_font();

    srand(time(NULL));

    while (!WindowShouldClose()) {
        BeginDrawing();
        
        game_loop();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
