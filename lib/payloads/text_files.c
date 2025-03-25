#include "text_files.h"
#include "payloads.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

char* how_to_play_filename = ".howtoplay";

char* how_to_play_text = "Hi!\n\
Before you start playing, I think I should make you aware of the rules!\n\
\n\
Controls: press the Up arrow to change gravity.\n\
Slide on the floor and ceiling to gain points and iFrames.\n\
\n\
iFrames allow you to break through blocks, but they go away when you do.\n\
250 points convert to 1 iFrame on the first 8 stages, then the cost becomes 125 points.\n\
Entering stages gives you 10 iFrames and sometimes increases the maximum you can have.\n\
Your score is on the top left, your iFrame count is on the bottom left.\n\
Stages show up on the bottom right.\n\
\n\
Good luck!\n\
And most importantly,\n\
DO NOT LOSE FOCUS!\n\
\n\
/ X Future\n\
...and ana_rchy";


char* credits_filename = ".glitchpass";

char* credits_text = "Thanks for playing!\n\
\n\
Game made by X Future. Ported by ana_rchy.\n\
Special thanks to jfero and tenler for helping X Future playtest.\n\
\n\
\n\
\n\
\n\
P.S. this file grants access to stages beyond F. Have fun!";

void write_and_open_howtoplay_if_nonexistant() {
    if (!FileExists(how_to_play_filename)) {
        SaveFileText(how_to_play_filename, how_to_play_text);
        
        // NOTE: there was a sleep here in the og but it just delays the game as a whole, lol
        open_text_file(how_to_play_filename);
    }
}

void write_and_open_credits_if_nonexistant() {
    if (!FileExists(credits_filename)) {
        SaveFileText(credits_filename, credits_text);

        sleep_ms(2000);
        open_text_file(credits_filename);
    }
}

//////////////////////////////////////////////////////////////////

void open_text_file(char* path) {
    char command[50];

    #if defined(__APPLE__) || defined(__MACH__) || defined(macintosh)
        if (!TextIsEqual(path, "")) {
            sprintf(command, "open %s &", path);
        } else {
            sprintf(command, "textedit &");
        }

    #elif defined(__unix) || defined(__unix__)
        if (posix_command_exists("xdg-open") && !TextIsEqual(path, "")) {
            sprintf(command, "xdg-open %s &", path);
            
        } else if (posix_command_exists("vim")) {
            sprintf(command, "$TERM vim %s &", path);
        } else if (posix_command_exists("nvim")) {
            sprintf(command, "$TERM nvim %s &", path);
        } else if (posix_command_exists("emacs")) {
            sprintf(command, "$TERM emacs %s &", path);
        } else if (posix_command_exists("nano")) {
            sprintf(command, "$TERM nano %s &", path);
        } else if (posix_command_exists("vi")) {
            sprintf(command, "$TERM vi %s &", path);
        } else if (posix_command_exists("ed")) {
            sprintf(command, "$TERM ed %s &", path);
        }

    #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        sprintf(command, "start notepad %s", path);

    #endif
    
    system(command);
}

//////////////////////////////////////////////////////////////////

void sleep_ms(int milliseconds) {
    #if defined(__unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) || defined(macintosh)
        #include <unistd.h>
        usleep(milliseconds * 1000);

    #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        #include <Windows.h>
        Sleep(milliseconds);

    #endif
}
