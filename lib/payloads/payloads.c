#include "payloads.h"
#include "../defines.h"
#include "process_opener.h"
#include <stdbool.h>
#include <math.h>
#include <raylib.h>

bool use_process_opener = false;
float time_since_process_opened = 0;

void payloads_loop(float time_since_game_start) {
    time_since_process_opened += GetFrameTime();

    if (!use_process_opener && time_since_game_start > PROCESS_OPENER_ACTIVATION_STAGE * STAGE_TIME + PROCESS_OPENER_INIT_DELAY) {
        use_process_opener = true;
        time_since_process_opened = PROCESS_OPENER_TIMER + 1;
    }

    if (use_process_opener && time_since_process_opened > PROCESS_OPENER_TIMER) {
        time_since_process_opened = fmod(time_since_process_opened, PROCESS_OPENER_TIMER);

        open_random_process();
    }

    // makes sure payloads dont fuck with inputs
    SetWindowFocused();
}
