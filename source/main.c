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

    printw("WarmaShark Develop Terminal\n");
    printw("This is dialogue lib1(tech test library):\n");
    refresh();

    struct scene_runtime runtime;
    sceneInit(&runtime);
    int dialogue_index = 0;
    char ch;
    while (dialogue_index + 1 <= runtime.dialogue1_size) {
        ch = getch();
        if (ch == ' ' or ch == '\n') {
            printw("%s\n", getCurrentEventText(dialogue_index));
            refresh();
            dialogue_index++;
            continue;
        }
        // use 'q' can force EXIT
        if (ch == 'q') {
            printw("Note: Develop terminal Exited due to User. Enter any key to exit.");
            break;
        }
    }
    // suspend program
    getch();

    endwin();
    printf("[For debug guy]: Remember, program may exit immediately after the last printw()\n");

    return 0;
}
