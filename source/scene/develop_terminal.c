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

int SceneStart_DevelopTerminal(struct WarmRuntimeConfig *runtime, WINDOW *win_handle)
{
    WarmLog_General(runtime, module_tag, "Entered the scene\n");

    // temp var for loop
    int dialogue_length = sizeof(dialogue) / sizeof(struct WarmDialogueEvent);
    int dialogue_index = 0;
    char getch_temp;

    do {
        int event_result = DialogueExecuteEvent(runtime, win_handle, &dialogue[dialogue_index]);
        if (event_result == 0) {
            getch_temp = getch();
            // space key or enter ker to continue
            if (getch_temp == ' ' or getch_temp == '\n') {
                dialogue_index++;
                continue;
            }
            // use 'q' can force EXIT
            if (getch_temp == 'q') {
                WarmLog_General(runtime, module_tag, "Dialogue breaked due to user input\n");
                break;
            }
        } else if (event_result == 1) {
            dialogue_index++;
            continue;
        }

        // TODO if exec to here, it's a serious warning...
        WarmLog_Warning(runtime, module_tag, "scene loop has a unknow issue");
        dialogue_index++;
    } while (dialogue_index + 1 <= dialogue_length);

    WarmLog_General(runtime, module_tag, "Exit the scene\n");
    return 0;
}
