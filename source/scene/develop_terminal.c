#include "develop_terminal.h"

#include <iso646.h>

#include <ncurses.h>

int sceneInit(struct scene_runtime *runtime);
char *getCurrentEventText(int index);

struct dialogue_event dialogue1[] = {
    {.text = "Hello"},
    {.text = "This is a Develop Terminal or just a dialogue tree for text output test."},
    {.text = "The protagonist of this program(or videogame), it's a shark. But live in another universe."},
    {.text = "Maybe his name is littleShark, sounds weird? But it is."},
    {.text = "Here is the last line(string pointer), be careful of this pointer index..."},
};

int sceneInit(struct scene_runtime *runtime)
{
    runtime->dialogue1_size = sizeof(dialogue1) / sizeof(struct dialogue_event);
    return 0;
}

char *getCurrentEventText(int index)
{
    return dialogue1[index].text;
}

int sceneStart_DevelopTerminal(WINDOW *win_handle)
{
    wprintw(win_handle, "WarmaShark Develop Terminal\n");
    wprintw(win_handle, "This is dialogue lib1(tech test library):\n");
    wrefresh(win_handle);

    struct scene_runtime runtime;
    sceneInit(&runtime);
    int dialogue_index = 0;
    char getch_temp;

    while (dialogue_index + 1 <= runtime.dialogue1_size) {
        getch_temp = getch();
        if (getch_temp == ' ' or getch_temp == '\n') {
            printw("%s\n", getCurrentEventText(dialogue_index));
            wrefresh(win_handle);
            dialogue_index++;
            continue;
        }
        // use 'q' can force EXIT
        if (getch_temp == 'q') {
            printw("Note: Develop terminal Exited due to User. Enter any key to exit.");
            wrefresh(win_handle);
            break;
        }
    }
    // suspend program after last dialogue
    getch();

    return 0;
}
