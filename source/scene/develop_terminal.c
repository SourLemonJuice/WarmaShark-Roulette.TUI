#include "scene/develop_terminal.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <ncurses.h>

#include "engine/engine_config.h"
#include "log/logger.h"

static char module_tag_[] = "scene - Develop Terminal";

struct DialogueEvent dialogue1[] = {
    {.await = true, .color_id = 1, .text = "Hello/你好"},
    {.await = true, .color_id = 0, .text = "，在这里可以按 q 键退出，Enter 或 Space 跳转到下一个对话。"},
    {.await = true, .color_id = 0, .text = "This is a Develop Terminal or just a test for a normal example dialogue tree."},
    {.await = true, .color_id = 0, .text = "But what's the difference, dialogue trees are just some data structure... We are all normal."},
    {.await = true, .color_id = 0, .text = "The protagonist of this program(or videogame), is a shark. But live in another universe."},
    {.await = true, .color_id = 0, .text = "沃玛/Warma created him. Maybe his name is littleShark?"},
    {.await = true, .color_id = 0, .text = "Cute, Evil, Complex, or have another Hidden Story?"},
    {.await = true, .color_id = 0, .text = "Here is the last line/event/string-pointer, be careful of this pointer index..."},
};

// did we really need this?
int SceneInit_DevelopTerminal(struct SceneCache_DevelopTerminal *cache)
{
    cache->dialogue1_size = sizeof(dialogue1) / sizeof(struct DialogueEvent);

    return 0;
}

int SceneStart_DevelopTerminal(struct WarmRuntimeConfig *engine_runtime, WINDOW *win_handle, int border_y, int border_x)
{
    WarmLog_General(engine_runtime, module_tag_, "Entered the scene\n");

    struct SceneCache_DevelopTerminal cache;
    SceneInit_DevelopTerminal(&cache);
    // temp var for loop
    int dialogue_index_ = 0;
    char getch_temp_;
    int win_max_y_;
    int win_max_x_;
    getmaxyx(win_handle, win_max_y_, win_max_x_);

    do {
        // clear the window
        for (int y = 0 + border_y; y <= win_max_y_ - border_y * 2; y++) {
            for (int x = 0 + border_x; x <= win_max_x_ - border_x * 2; x++) {
                // don't use delch(), it's not working like you want, check the docs
                // mvwdelch(win_handle, y, x);
                mvwaddch(win_handle, y, x, ' ');
            }
        }
        // reset to first line
        wmove(win_handle, 0 + border_y, 0 + border_x);

        WarmLog_General(engine_runtime, module_tag_, ".text = %s .color_id = %d\n", dialogue1[dialogue_index_].text,
                        dialogue1[dialogue_index_].color_id);

        // TODO so why it's looked so weird
        waddch(win_handle, 't' | COLOR_PAIR(1)); // this can work
        attron(COLOR_PAIR(dialogue1[dialogue_index_].color_id)); // but this not
        wprintw(win_handle, "%s", dialogue1[dialogue_index_].text);
        attroff(COLOR_PAIR(dialogue1[dialogue_index_].color_id));
        wrefresh(win_handle);

        // if don't need wait a key press
        if (dialogue1[dialogue_index_].await == false) {
            dialogue_index_++;
            continue;
        }

        dialogue_index_++;

        getch_temp_ = getch();
        // space key or enter ker to continue
        if (getch_temp_ == ' ' or getch_temp_ == '\n') {
            continue;
        }
        // use 'q' can force EXIT
        if (getch_temp_ == 'q') {
            WarmLog_General(engine_runtime, module_tag_, "Dialogue breaked due to user input\n");
            break;
        }
    } while (dialogue_index_ + 1 <= cache.dialogue1_size);

    WarmLog_General(engine_runtime, module_tag_, "Exit the scene\n");
    return 0;
}
