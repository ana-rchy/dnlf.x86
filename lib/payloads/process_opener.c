#include "process_opener.h"
#include "../defines.h"
#include "payloads.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void open_random_process() {
    switch (rand_range(5, 10)) {
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

void open_link(char* link) {
    char command[200];

    #if defined(__APPLE__) || defined(__MACH__) || defined(macintosh)
        sprintf(command, "open %s &", link);

    #elif defined(__unix) || defined(__unix__)
        if (posix_command_exists("xdg-open")) {
            sprintf(command, "xdg-open %s &", link);
        } else if (posix_command_exists("python")) {
            sprintf(command, "python -m webbrowser %s", link);
        }
       
    #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        sprintf(command, "rundll32 url.dll,FileProtocolHandler %s", link);

    #endif

    system(command);
}
