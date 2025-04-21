#include "text_files.h"
#include "../defines.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#if defined(IS_UNIX)
    #include <unistd.h>
#elif defined(IS_WINDOWS)
    #include <Windows.h>
#endif

char* unix_text_editors[] = { "vim", "nvim", "emacs", "nano", "vi", "ed", NULL };


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
    #if defined(IS_MAC)
        if (!TextIsEqual(path, "")) {
            run_command("open", (char*[]) { path, "&", NULL });
        } else {
            system("textedit &");
        }

    #elif defined(IS_BASED_UNIX)
        if (posix_command_exists("xdg-open") && !TextIsEqual(path, "")) {
            run_command("xdg-open", (char*[]) { path, NULL });
        } else {
            int i = get_first_valid_command_index(unix_text_editors);

            open_posix_terminal((char*[]) { unix_text_editors[i], NULL });
        }

    #elif defined(IS_WINDOWS)
        run_command("start notepad", (char*[]) { path, NULL });

    #endif
}

//////////////////////////////////////////////////////////////////

void sleep_ms(int milliseconds) {
    #if defined(IS_UNIX)
        usleep(milliseconds * 1000);

    #elif defined(IS_WINDOWS)
        Sleep(milliseconds);

    #endif
}
