#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 200

char* unix_terminals[] = { "gnome-terminal", "konsole", "alacritty", "kitty", "blackbox-terminal", "mate-terminal", "xfce4-terminal", "zutty", "xterm", NULL };


bool posix_command_exists(char* command) {
    char buffer[80];
    snprintf(buffer, 80, "which %s > /dev/null 2>&1", command);
    
    return !system(buffer);
}

void run_command(char* command, char* args[]) {
    char temp_buffer[BUFFER_SIZE];
    char run_buffer[BUFFER_SIZE];

    snprintf(run_buffer, BUFFER_SIZE, "%s", command);

    int i = -1;
    while (args != NULL && args[++i] != NULL) {
        snprintf(temp_buffer, BUFFER_SIZE, "%s", run_buffer);
        snprintf(run_buffer, BUFFER_SIZE, "%s %s", temp_buffer, args[i]);
    }

    system(run_buffer);
}

//////////////////////////////////////////////////////////////////

int get_first_valid_command_index(char* commands[]) {
    int i = -1;
    while (commands[++i] != NULL) {
        if (posix_command_exists(commands[i])) {
            return i;
        }
    }

    return -1;
}

void run_first_valid_command(char* commands[], char* args[]) {
    int i = -1;
    while (commands[++i] != NULL) {
        if (posix_command_exists(commands[i])) {
            run_command(commands[i], args);
            break;
        }
    }

    if (commands[i] == NULL) {
        printf("execute_first_command_that_exists: no valid commands");
        return;
    }
}

//////////////////////////////////////////////////////////////////

void open_posix_terminal(char* args[]) {
    #if defined(__APPLE__) || defined(__MACH__) || defined(macintosh)

    #elif defined(__unix) || defined(__unix__)
        if (getenv("TERM") != NULL && posix_command_exists("$TERM")) {
            run_command("$TERM", args);
        } else {
            run_first_valid_command(unix_terminals, args);
        }

    #endif
}
