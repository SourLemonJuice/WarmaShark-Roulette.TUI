#include <iso646.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

#include "engine/engine_config.h"
#include "log/logger.h"
#include "scene/develop_terminal.h"

int main(int argc, char *argv[])
{
    // init engine
    struct WarmRuntimeConfig runtime_config_;
    EngineRuntimeInit(&runtime_config_);

    // if have any arguments, then break program
    if (argc >= 2) {
        WarmLog_Warning(&runtime_config_, "main", "there is a CLI argument input here, we don't use it");
    }

    /* init ncurse std screen */
    initscr();
    cbreak();
    noecho();

    // get maximum screen size
    int max_y_;
    int max_x_;
    getmaxyx(stdscr, max_y_, max_x_);
    WarmLog_General(&runtime_config_, "main", "MAX screen X: %d, Y: %d\n", max_x_, max_y_);

    // logging
    WarmLog_General(&runtime_config_, "main", "ncurses has inited, starting Developer Terminal scene\n");

    wprintw(stdscr, "Yeah, Welcome to WarmaShark Develop Terminal\n");
    wprintw(stdscr, "======== ======== ========\n");
    wrefresh(stdscr);
    // create a window for develop terminal scene
    WINDOW *window_ = newwin((max_y_ - 2) * 0.6, max_x_ * 0.7, 2, 0);
    box(window_, 0, 0);
    wrefresh(window_);
    // start test scene
    SceneStart_DevelopTerminal(&runtime_config_, window_, 1, 1);

    // show end info(full screen)
    werase(stdscr);
    wprintw(stdscr, "==== WarmaShark[Under Development] ====\n");
    wprintw(stdscr, "Made With Open Source Softwares\n");
    wrefresh(stdscr);
    // suspend program
    getch();

    // freeup everything
    EngineRuntimeFreeup(&runtime_config_);
    endwin();

    return 0;
}
