#include "scene/develop_terminal.h"

#include <iso646.h>

#include <ncurses.h>

#include "engine/engine_config.h"
#include "log/logger.h"

struct DialogueEvent dialogue1[] = {
    {.text = "Hello"},
    {.text = "This is a Develop Terminal or just a test for a normal example dialogue tree."},
    {.text = "But what's the difference, dialogue trees are just some data structure... We are all normal."},
    {.text = "The protagonist of this program(or videogame), is a shark. But live in another universe."},
    {.text = "沃玛/Warma created him. Maybe his name is littleShark?"},
    {.text = "Cute, Evil, Complex, or have another Hidden Story?"},
    {.text = "Here is the last line/event/string-pointer, be careful of this pointer index..."},
};

int SceneInit_DevelopTerminal(struct SceneCache_DevelopTerminal *cache)
{
    cache->dialogue1_size = sizeof(dialogue1) / sizeof(struct DialogueEvent);
    return 0;
}

int SceneStart_DevelopTerminal(struct WarmRuntimeConfig *engine_runtime, WINDOW *win_handle)
{
    char module_tag_[] = "scene - Develop Terminal";

    WarmLog_General(engine_runtime, module_tag_, "Entered the scene\n");
    int max_y_;
    int max_x_;
    getmaxyx(stdscr, max_y_, max_x_);
    WarmLog_General(engine_runtime, module_tag_, "MAX screen X: %d, Y: %d\n", max_x_, max_y_);

    wprintw(win_handle, "Yeah, WarmaShark Develop Terminal\n");
    wprintw(win_handle, "Here is the dialogue tree 1(just for tech test)\n");
    wprintw(win_handle, "==== ==== ====\n");
    wrefresh(win_handle);

    struct SceneCache_DevelopTerminal cache;
    SceneInit_DevelopTerminal(&cache);
    // temp var for loop
    int dialogue_index = 0;
    char getch_temp;
    int cursorX;
    int cursorY;
    getyx(win_handle, cursorY, cursorX);

    while (dialogue_index + 1 <= cache.dialogue1_size) {
        getch_temp = getch();
        if (getch_temp == ' ' or getch_temp == '\n') {
            wmove(win_handle, cursorY, cursorX);
            wclrtoeol(win_handle);
            wprintw(win_handle, "%s", dialogue1[dialogue_index].text);
            wrefresh(win_handle);

            dialogue_index++;
            continue;
        }
        // use 'q' can force EXIT
        if (getch_temp == 'q') {
            printw("Note: Develop terminal Exited due to User. Enter any key to exit.");
            wrefresh(win_handle);
            WarmLog_General(engine_runtime, module_tag_, "Dialogue breaked due to user input\n");
            break;
        }
    }
    // suspend program after last dialogue
    getch();

    WarmLog_General(engine_runtime, module_tag_, "Exit the scene\n");
    return 0;
}
