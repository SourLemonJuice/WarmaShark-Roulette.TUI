#include <iso646.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

#include "engine/engine_config.h"
#include "log/logger.h"
#include "scene/develop_terminal.h"

int main(void)
{
    struct WarmRuntimeConfig runtime_config;
    EngineRuntimeInit(&runtime_config);

    /* init ncurse std screen */
    initscr();
    cbreak();
    noecho();

    // logging
    WarmLog_General(&runtime_config, "main", "ncurses has inited, starting Developer Terminal scene\n");

    // start test scene
    SceneStart_DevelopTerminal(&runtime_config, stdscr);

    // show end info(full screen)
    werase(stdscr);
    wprintw(stdscr, "==== WarmaShark[Under Development] ====\n");
    wprintw(stdscr, "Made With Open Source Softwares\n");
    wrefresh(stdscr);
    // suspend program
    getch();

    // freeup everything
    EngineRuntimeFreeup(&runtime_config);
    endwin();

    return 0;
}
