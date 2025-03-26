#include "terminal.h"
#include "../defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#if defined(IS_UNIX)
    #include <unistd.h>
#endif

#define BUFFER_SIZE 200

char* unix_terminals[] = { "gnome-terminal", "konsole", "alacritty", "kitty", "blackbox-terminal", "mate-terminal", "xfce4-terminal", "zutty", "xterm", NULL };


bool posix_command_exists(char* command) {
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "which %s > /dev/null 2>&1", command);
    
    return !system(buffer);
}

void run_command(char* command, char* args[]) {
    int args_count = -1;
    while (args[++args_count] != NULL) {}

    char* all_args[args_count + 2];
    all_args[0] = command;

    for (int i = 1; i < args_count + 1; i++) {
        all_args[i] = args[i - 1];
    }

    all_args[args_count + 1] = NULL;


    #if defined(IS_UNIX)
        pid_t process_id = fork();
        
        // child
        if (process_id == 0) {
            execvp(command, all_args);

            perror("run_command execvp failed");
            exit(EXIT_FAILURE);
        }

        // parent
        if (process_id < 0) {
            perror("run_command fork failed");
            exit(EXIT_FAILURE);
        }

    #elif defined(IS_WINDOWS)

    #endif
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
    #if defined(IS_MAC)

    #elif defined(IS_BASED_UNIX)
        if (getenv("TERM") != NULL && posix_command_exists("$TERM")) {
            run_command("$TERM", args);
        } else {
            run_first_valid_command(unix_terminals, args);
        }

    #endif
}
