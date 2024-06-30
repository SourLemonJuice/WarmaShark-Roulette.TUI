#include <iso646.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "log/logger.h"
#include "runtime.h"
#include "scene/develop_terminal.h"

int main(int argc, char *argv[])
{
    // init engine
    struct WarmRuntimeConfig runtime_config_;
    EngineRuntimeInit(&runtime_config_);

    // if have any arguments, then break program
    if (argc >= 2) {
        WarmLog_Warning(&runtime_config_, "main", "there is a CLI argument input here, we don't use it\n");
    }

    /* init ncurse std screen */
    initscr();
    cbreak();
    noecho();
    // init clolor
    if (has_colors() == false) {
        wprintw(stdscr, "ERROR: The terminal don't support color output.");
        wgetch(stdscr); // suspend
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // get maximum screen size, used to calcuate the size of scene window
    int max_y_;
    int max_x_;
    getmaxyx(stdscr, max_y_, max_x_);
    WarmLog_General(&runtime_config_, "main", "MAX screen X: %d, Y: %d\n", max_x_, max_y_);

    // logging
    WarmLog_General(&runtime_config_, "main", "ncurses has inited, starting Developer Terminal scene\n");

    attron(COLOR_PAIR(1));
    wprintw(stdscr, "Yeah, Welcome to WarmaShark Develop Terminal\n");
    attroff(COLOR_PAIR(1));
    wprintw(stdscr, "========:========:========\n");
    wrefresh(stdscr);
    // create a window for develop terminal scene
    WINDOW *window_ = newwin((max_y_ - 2) * 0.4, max_x_ * 0.7, 2, 0);
    box(window_, 0, 0);
    wrefresh(window_);
    delwin(window_);
    // new windows without border
    window_ = newwin(((max_y_ - 2) * 0.4) - 2, (max_x_ * 0.7) - 2, 3, 1);
    // start test scene
    SceneStart_DevelopTerminal(&runtime_config_, window_);

    // show end info(full screen)
    werase(stdscr);
    attron(COLOR_PAIR(2));
    wprintw(stdscr, "--> WarmaShark[Under Development]\n");
    attroff(COLOR_PAIR(2));
    wprintw(stdscr, "Made With Open Source Softwares\n");
    wprintw(stdscr, "> Press any key to EXIT <\n");
    wrefresh(stdscr);
    // suspend program
    wgetch(stdscr);

    // freeup everything
    EngineRuntimeFreeup(&runtime_config_);
    endwin();

    return 0;
}
