#include "payloads.h"
#include "../defines.h"
#include "process_opener.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

char* unix_terminals[] = { "gnome-terminal", "konsole", "alacritty", "kitty", "blackbox-terminal", "mate-terminal", "xfce4-terminal", "zutty", "xterm", NULL };

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

        /*open_random_process();*/
    }
    run_command(200, "kitty", NULL);

    // makes sure payloads dont fuck with inputs
    SetWindowFocused();
}

//////////////////////////////////////////////////////////////////

bool posix_command_exists(char* command) {
    char buffer[50];
    sprintf(buffer, "which %s > /dev/null 2>&1", command);
    
    return !system(buffer);
}

void run_command(int buffer_size, char* command, char* args[]) {
    char temp_buffer[buffer_size];
    char run_buffer[buffer_size];

    snprintf(run_buffer, buffer_size, "%s", command);

    int i = -1;
    while (args != NULL && args[++i] != NULL) {
        snprintf(temp_buffer, buffer_size, "%s", run_buffer);
        snprintf(run_buffer, buffer_size, "%s %s", temp_buffer, args[i]);
    }

    printf("%s\n", run_buffer);
    /*system(buffer);*/
}

void run_formatted_command(int buffer_size, char* command, char* format, ...) {
    char format_buffer[buffer_size];
    char run_buffer[buffer_size];

    va_list args;
    va_start(args, format);

    vprintf("%s\n", args);
    
    vsprintf(format_buffer, format, args);
    sprintf(run_buffer, "%s %s", command, format_buffer);

    va_end(args);

    /*system(run_buffer);*/
}

void run_first_command_that_exists(int buffer_size, char* commands[], char* format, ...) {
    va_list args;
    va_start(args, format);

    int i = -1;
    while (commands[++i] != NULL) {
        if (posix_command_exists(commands[i])) {
            run_formatted_command(buffer_size, commands[i], format, args);
            break;
        }
    }

    va_end(args);

    if (commands[i] == NULL) {
        printf("execute_first_command_that_exists: no valid commands");
        return;
    }
}

//////////////////////////////////////////////////////////////////

void open_posix_terminal(char* args_format_str, ...) {
    va_list args;

    #if defined(__APPLE__) || defined(__MACH__) || defined(macintosh)

    #elif defined(__unix) || defined(__unix__)
        if (getenv("TERM") != NULL && posix_command_exists("$TERM")) {
            run_formatted_command(50, "$TERM", args_format_str, args);
        } else {
            run_first_command_that_exists(100, unix_terminals, args_format_str, args);
        }

    #endif
}
