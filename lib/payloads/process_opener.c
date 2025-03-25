#include "process_opener.h"
#include "../defines.h"
#include "payloads.h"
#include "text_files.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

char* unix_file_managers[] = { "xdg-open", "nemo", "nautilus", "dolphin", "thunar", "caja", NULL };
char* unix_web_browsers[] = { "xdg-open", "librewolf", "firefox", NULL };


void open_random_process() {
    switch (rand_range(5, 10)) {
        /*case 3:*/
        /*    open_text_file("");*/
        /*    break;*/
        /**/
        /*case 4:*/
        /*    open_file_manager();*/
        /*    break;*/

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
    #if defined(__APPLE__) || defined(__MACH__) || defined(macintosh)

    #elif defined(__unix) || defined(__unix__)
        // open terminal
        if (posix_command_exists("$TERM")) {
            system("$TERM &");
        }
       
    #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        system("start calc");

    #endif
}

void open_file_manager() {
    #if defined(__APPLE__) || defined(__MACH__) || defined(macintosh)
        system("open ~ &");

    #elif defined(__unix) || defined(__unix__)
        /*run_first_command_that_exists(unix_file_managers, "~", 50);*/
       
    #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        system("start explorer");

    #endif
}

void open_link(char* link) {
    const int BUFFER_SIZE = 200;

    #if defined(__APPLE__) || defined(__MACH__) || defined(macintosh)
        run_formatted_command(BUFFER_SIZE, "open", "%s &", link);

    #elif defined(__unix) || defined(__unix__)
        run_first_command_that_exists(BUFFER_SIZE, unix_web_browsers, "%s &", link);
       
    #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        run_formatted_command(BUFFER_SIZE, "rundll32 url.dll,FileProtocolHandler", "%s", link);

        char command[BUFFER_SIZE];
        sprintf(command, "rundll32 url.dll,FileProtocolHandler %s", link);

        system(command);

    #endif
}
