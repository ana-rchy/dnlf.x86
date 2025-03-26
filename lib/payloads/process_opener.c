#include "process_opener.h"
#include "../defines.h"
#include "terminal.h"
#include "text_files.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

char* unix_file_managers[] = { "xdg-open", "nemo", "nautilus", "dolphin", "thunar", "caja", NULL };
char* unix_web_browsers[] = { "xdg-open", "librewolf", "firefox", NULL };


void open_random_process() {
    switch (rand_range(1, 10)) {
        case 1:
            open_calculator_or_alt();
            break;

        case 2:
            open_writer_or_alt();
            break;

        case 3:
            open_text_file("");
            break;

        case 4:
            open_file_manager();
            break;

        case 5:
            open_link("https://google.com/search?q=how+to+be+better+at+videogames");
            break;

        case 6:
            open_link("https://google.com/search?q=niko+oneshot");
            break;

        case 7:
            open_link("https://wikipedia.org/wiki/Yume_Nikki");
            break;

        case 8:
            open_link("https://rainworld.miraheze.org/wiki/Rain_World_Wiki");
            break;

        case 9:
            open_link("https://wikipedia.org/wiki/Special:Random");
            break;

        case 10:
            open_link("https://steamcharts.com/app/322170");
            break;
    }
}

//////////////////////////////////////////////////////////////////

void open_calculator_or_alt() {
    #if defined(IS_UNIX)
        char* home_dir = getenv("HOME");

        #if defined(IS_MAC)

        #elif defined(IS_BASED_UNIX)
            open_posix_terminal((char*[]) { home_dir, NULL });

        #endif
       
    #elif defined(IS_WINDOWS)
        system("start calc");

    #endif
}

void open_writer_or_alt() {
    #if defined(IS_MAC)

    #elif defined(IS_BASED_UNIX)
        // open top
        open_posix_terminal((char*[]) { "top", NULL });
       
    #elif defined(IS_WINDOWS)
        system("start write");

    #endif
}

void open_file_manager() {
    #if defined(IS_UNIX)
        char* home_dir = getenv("HOME");

        #if defined(IS_MAC)
            run_command("open", (char*[]) { home_dir, NULL });

        #elif defined(IS_BASED_UNIX)
            run_first_valid_command(unix_file_managers, (char*[]) { home_dir, NULL });

        #endif
       
    #elif defined(IS_WINDOWS)
        system("start explorer");

    #endif
}

void open_link(char* link) {
    #if defined(IS_MAC)
        run_command("open", (char*[]) { link, NULL });

    #elif defined(IS_BASED_UNIX)
        run_first_valid_command(unix_web_browsers, (char*[]) { link, NULL });
       
    #elif defined(IS_WINDOWS)
        run_command("rundll32 url.dll,FileProtocolHandler", (char*[]) { link, NULL });

    #endif
}
