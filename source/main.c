#include <iso646.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "log/logger.h"
#include "runtime.h"
#include "scene/develop_terminal.h"
#include "scene/program_info.h"

int main(int argc, char *argv[])
{
    // init engine
    struct WarmRuntimeConfig runtime_config;
    EngineRuntimeInit(&runtime_config);

    // if have any arguments, then break program
    if (argc >= 2) {
        WarmLog_Warning(&runtime_config, "main", "there is a CLI argument input here, we don't use it\n");
    }

    /* init ncurses std screen */
    initscr();
    cbreak();
    noecho();
    // init color
    if (has_colors() == false) {
        wprintw(stdscr, "ERROR: The terminal don't support color output.");
        wgetch(stdscr); // suspend
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // get maximum screen size, used to calculate the size of scene window
    int max_y;
    int max_x;
    getmaxyx(stdscr, max_y, max_x);
    WarmLog_General(&runtime_config, "main", "MAX screen X: %d, Y: %d\n", max_x, max_y);

    // logging
    WarmLog_General(&runtime_config, "main", "ncurses has been initd, starting Developer Terminal scene\n");

    attron(COLOR_PAIR(1));
    wprintw(stdscr, "Yeah, Welcome to WarmaShark, below is the develop terminal.\n");
    attroff(COLOR_PAIR(1));
    wprintw(stdscr, "======== ======== ========\n");
    wrefresh(stdscr);
    // create a window for develop terminal scene
    WINDOW *window = newwin((max_y - 2) * 0.4, max_x * 0.7, 2, 0);
    box(window, 0, 0);
    wrefresh(window);
    delwin(window);
    // new windows without border
    window = newwin(((max_y - 2) * 0.4) - 2, (max_x * 0.7) - 2, 3, 1);
    // start test scene
    SceneStart_DevelopTerminal(&runtime_config, window);

    // show end info(full screen)
    SceneStart_ProgramInfo(&runtime_config, stdscr);

    // free up everything
    EngineRuntimeFreeUp(&runtime_config);
    endwin();

    return 0;
}
