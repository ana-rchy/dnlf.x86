#include <stdio.h>
#include <raylib.h>
#include "lib/defines.h"
#include "lib/renderer.h"
#include "lib/level.h"

int main() {
    setup_renderer();

    Font font = LoadFont("font.png");
    
    setup_level();

    while (!WindowShouldClose()) {
        setup_screen();

        draw_screen();
    }

    return 0;
}
