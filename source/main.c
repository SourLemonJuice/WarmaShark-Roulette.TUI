#include <stdio.h>
#include <iso646.h>
#include <stdlib.h>

#include <ncurses.h>

#include "scene/develop_terminal.h"

int main(void)
{
    /* init ncurse std screen */
    initscr();
    cbreak();
    noecho();

    // start test scene
    sceneStart_DevelopTerminal(stdscr);
    // show end info(full screen)
    werase(stdscr);
    wprintw(stdscr, "It's the last suspend of the program, just for debug now.\n");
    wprintw(stdscr, "For debug guy, remember program may exit immediately after the last printw()\n");
    wrefresh(stdscr);
    // wait a key
    getch();

    endwin();

    return 0;
}
