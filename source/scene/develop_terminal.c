#include "develop_terminal.h"

#include <iso646.h>

#include <ncurses.h>

int sceneInit(struct scene_runtime *runtime);
char *getCurrentEventText(int index);

struct dialogue_event dialogue1[] = {
    {.text = "Hello"},
    {.text = "This is a Develop Terminal or just a test for a normal example dialogue tree."},
    {.text = "But what's the difference, dialogue trees are just some data structure... We are all normal."},
    {.text = "The protagonist of this program(or videogame), is a shark. But live in another universe."},
    {.text = "沃玛/Warma created him. Maybe his name is littleShark?"},
    {.text = "Cute, Evil, Complex, or have another Hidden Story?"},
    {.text = "Here is the last line/event/string-pointer, be careful of this pointer index..."},
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
    wprintw(win_handle, "Yeah, WarmaShark Develop Terminal\n");
    wprintw(win_handle, "Here is the dialogue tree 1(just for tech test):\n");
    wrefresh(win_handle);

    struct scene_runtime runtime;
    sceneInit(&runtime);
    // temp var for loop
    int dialogue_index = 0;
    char getch_temp;
    int cursorX;
    int cursorY;
    getyx(win_handle, cursorY, cursorX);

    while (dialogue_index + 1 <= runtime.dialogue1_size) {
        getch_temp = getch();
        if (getch_temp == ' ' or getch_temp == '\n') {
            wmove(win_handle, cursorY, cursorX);
            wclrtoeol(win_handle);
            wprintw(win_handle, "%s", getCurrentEventText(dialogue_index));
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
