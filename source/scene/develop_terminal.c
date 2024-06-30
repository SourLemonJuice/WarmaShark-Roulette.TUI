#include "scene/develop_terminal.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <ncurses.h>

#include "log/logger.h"
#include "runtime.h"

static const char module_tag_[] = "scene - Develop Terminal";

static const struct DialogueEvent dialogue1[] = {
    {.finished = false, .color_id = 1, .text = "Hello/你好"},
    {.finished = true, .color_id = 0, .text = "，在这里可以按 q 键退出，Enter 或 Space 跳转到下一个对话。"},
    {.finished = true,
     .color_id = 0,
     .text = "This is a Develop Terminal or just a test for a normal example dialogue tree."},
    {.finished = true,
     .color_id = 0,
     .text = "But what's the difference, dialogue trees are just some data structure... We are all normal."},
    {.finished = true,
     .color_id = 0,
     .text = "The protagonist of this program(or videogame), is a shark. But live in another universe."},
    {.finished = true, .color_id = 0, .text = "沃玛/Warma created him. Maybe his name is littleShark?"},
    {.finished = true, .color_id = 0, .text = "Cute, Evil, Complex, or have another Hidden Story?"},
    {.finished = true,
     .color_id = 0,
     .text = "Here is the last line/event/string-pointer, be careful of this pointer index..."},
};

int SceneStart_DevelopTerminal(struct WarmRuntimeConfig *engine_runtime, WINDOW *win_handle)
{
    WarmLog_General(engine_runtime, module_tag_, "Entered the scene\n");

    // temp var for loop
    int dialogue_length_ = sizeof(dialogue1) / sizeof(struct DialogueEvent);
    int dialogue_index_ = 0;
    char getch_temp_;
    // max windows X Y, and init them
    int win_max_y_;
    int win_max_x_;
    getmaxyx(win_handle, win_max_y_, win_max_x_);

    // reset to first line
    wmove(win_handle, 0, 0);

    do {
        // a log for debug
        WarmLog_General(engine_runtime, module_tag_, ".color_id = %d, .text = %s\n",
                        dialogue1[dialogue_index_].color_id, dialogue1[dialogue_index_].text);

        // main print
        wattron(win_handle, COLOR_PAIR(dialogue1[dialogue_index_].color_id));
        wprintw(win_handle, "%s", dialogue1[dialogue_index_].text);
        wattroff(win_handle, COLOR_PAIR(dialogue1[dialogue_index_].color_id));
        wrefresh(win_handle);

        // if don't need wait a key press
        if (dialogue1[dialogue_index_].finished == false) {
            dialogue_index_++;
            continue;
        }

        // clear the window
        werase(win_handle);
        // reset to first line
        wmove(win_handle, 0, 0);

        getch_temp_ = getch();
        // space key or enter ker to continue
        if (getch_temp_ == ' ' or getch_temp_ == '\n') {
            dialogue_index_++;
            continue;
        }
        // use 'q' can force EXIT
        if (getch_temp_ == 'q') {
            WarmLog_General(engine_runtime, module_tag_, "Dialogue breaked due to user input\n");
            break;
        }

        // TODO if exec to here, it's a serious warning...
        WarmLog_Warning(engine_runtime, module_tag_, "scene loop has a unknow issue");
        dialogue_index_++;
    } while (dialogue_index_ + 1 <= dialogue_length_);

    WarmLog_General(engine_runtime, module_tag_, "Exit the scene\n");
    return 0;
}
