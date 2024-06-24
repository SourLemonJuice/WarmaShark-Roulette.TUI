#include <stdio.h>
#include <iso646.h>
#include <stdlib.h>

#include <ncurses.h>

int main(void)
{
    char *dialogue_tree1[] = {
        "Hello",
        "This is a Develop Terminal or just a dialogue tree for text output test.",
        "The protagonist of this program(or videogame), it's a shark. But live in another universe.",
        "Maybe his name is littleShark, sounds weird? But it is.",
        "Here is the last line(string pointer), be careful of this pointer index...",
    };
    int dialogue_tree1_entries_num = sizeof(dialogue_tree1) / sizeof(char*);

    initscr();
    cbreak();
    noecho();

    printw("WarmaShark Develop Terminal\n");
    printw("This is dialogue lib1(tech test library):\n");
    refresh();

    char ch;
    int dialogue_index = 0;
    while (dialogue_index + 1 <= dialogue_tree1_entries_num) {
        ch = getch();
        if (ch == ' ' or ch == '\n') {
            printw("%s\n", dialogue_tree1[dialogue_index]);
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
