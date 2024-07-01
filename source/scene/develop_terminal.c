#include "develop_terminal.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <ncurses.h>

#include "dialogue.h"
#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "scene - Develop Terminal";

static const struct WarmDialogueEvent dialogue[] = {
    {.finished = false, .attribute = COLOR_PAIR(1), .text = "Hello/你好"},
    {.finished = true,
     .attribute = COLOR_PAIR(0),
     .text = "，在这里可以按 q 键退出，Enter 或 Space 跳转到下一个对话。"},
    {.finished = true,
     .attribute = COLOR_PAIR(0),
     .text = "This is a Develop Terminal or just a test for a normal example dialogue tree."},
    {.finished = true,
     .attribute = COLOR_PAIR(0),
     .text = "But what's the difference, dialogue trees are just some data structure... We are all normal."},
    {.finished = true,
     .attribute = COLOR_PAIR(0),
     .text = "The protagonist of this program(or videogame), is a shark. But live in another universe."},
    {.finished = true, .attribute = COLOR_PAIR(0), .text = "沃玛/Warma created him. Maybe his name is littleShark?"},
    {.finished = true, .attribute = COLOR_PAIR(0), .text = "Cute, Evil, Complex, or have another Hidden Story?"},
    {.finished = true,
     .attribute = COLOR_PAIR(0),
     .text = "Here is the last line/event/string-pointer, be careful of this pointer index..."},
};

/*
    If result is non zero, means have some problem.
 */
int SceneStart_DevelopTerminal(struct WarmRuntimeConfig *runtime, WINDOW *win_handle)
{
    WarmLog_General(runtime, module_tag, "Entered the scene\n");

    // temp var for loop
    int dialogue_length = sizeof(dialogue) / sizeof(struct WarmDialogueEvent);
    int dialogue_index = 0;
    char getch_temp;

    // just for test
    struct WarmSelectorActionEvent selector_event[4] = {
        {.string = "test1(exit)",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 0,
         .position_x = 0},
        {.string = "test2(exit)",
         .attribute = A_DIM,
         .attribute_highlight = A_STANDOUT,
         .position_y = 1,
         .position_x = 0},
        {.string = "Hello World 3(exit)",
         .attribute = A_DIM,
         .attribute_highlight = A_STANDOUT,
         .position_y = 2,
         .position_x = 0},
        {.string = "Main Dialogue",
         .attribute = A_BOLD,
         .attribute_highlight = A_STANDOUT,
         .position_y = 3,
         .position_x = 0},
    };
    int ret = DialogueSelector(runtime, win_handle, selector_event, 4);
    WarmLog_General(runtime, module_tag, "selector result %d\n", ret);
    // if not chose the "main dialogue" then exit this scene
    if (ret != 3) {
        return 0;
    }

    do {
        int event_result = DialogueExecuteEvent(runtime, win_handle, &dialogue[dialogue_index]);
        if (event_result == 0) {
            // loop for get key
            while (true) {
                getch_temp = getch();
                // space key or enter ker to continue
                if (getch_temp == ' ' or getch_temp == '\n') { // space key or enter key to continue the dialogue
                    dialogue_index++;
                    break;
                } else if (getch_temp == 'q') { // use 'q' can force EXIT
                    WarmLog_General(runtime, module_tag, "Dialogue break due to user input\n");
                    return 0;
                } else {
                    continue;
                }
            }
        } else if (event_result == 1) {
            dialogue_index++;
            continue;
        } else {
            WarmLog_Warning(runtime, module_tag, "unknow result of DialogueExecuteEvent()");
            return 1;
        }
    } while (dialogue_index + 1 <= dialogue_length);

    WarmLog_General(runtime, module_tag, "Exit the scene normally\n");
    return 0;
}
