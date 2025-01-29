#include <stdio.h>
#include <raylib.h>
#include "lib/defines.h"
#include "lib/renderer.h"
#include "lib/level.h"

int main() {
    setup_renderer();

    setup_level();

    generate_next_screen(0);

    while (!WindowShouldClose()) {
        refresh_screen();

        draw_level_to_screen();
        draw_screen();
    }

    return 0;
}
