#include <stdio.h>
#include <iso646.h>
#include <stdlib.h>

#include <ncurses.h>

int main(void)
{
    char *dialogue_lib1[] = {
        "hello.",
        "Who are you?",
        "I'm littleShark, maybe sounds weird, but this is my name!",
        "Here is the last line, can you see me? 233",
    };
    int dialogue_lib1_entries_num = sizeof(dialogue_lib1) / sizeof(char*);

    initscr();
    cbreak();
    noecho();

    printw("WarmaShark Develop Terminal\n");
    printw("This is dialogue lib1(tech test library):\n");
    refresh();

    char ch;
    int dialogue_index = 0;
    while (dialogue_index + 1 <= dialogue_lib1_entries_num) {
        ch = getch();
        if (ch == ' ' or ch == '\n') {
            printw("%s\n", dialogue_lib1[dialogue_index]);
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
