#include <raylib.h>

#define SCREEN_X 1024
#define SCREEN_Y 576
#define SCREEN_TEXT_X 128
#define SCREEN_TEXT_Y 48
#define UNIT_X (int) (SCREEN_X / SCREEN_TEXT_X)
#define UNIT_Y (int) (SCREEN_Y / SCREEN_TEXT_Y)

int main() {
    InitWindow(SCREEN_X, SCREEN_Y, "DO NOT LOSE FOCUS.x86");
    SetTargetFPS(240);

    Font font = LoadFont("font.png");

    char buffer[SCREEN_TEXT_X][SCREEN_TEXT_Y] = { ' ', ' ', ' ', ' ', ' ', '@' };
    
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        for (int i = 0; i < SCREEN_TEXT_X; i++) {
            for (int j = 0; j < SCREEN_TEXT_Y; j++) {
                DrawTextEx(font, &buffer[i][j], (Vector2) { UNIT_X * i, UNIT_Y * j }, 12, 0, BLACK);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
