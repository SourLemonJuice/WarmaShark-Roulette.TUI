#include "scene/develop_terminal.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>

#include "control/dialogue2.h"
#include "control/selector.h"
#include "control/trigger.h"
#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "Scene.Develop-Terminal";

/*
    Result:
        0: continue
        1: ERROR
 */
static int GetKeyToContinue_(struct WarmRuntime *runtime, WINDOW *win)
{
    int input;
    while (true) {
        input = wgetch(win);
        if (input == ' ' or input == '\n') {
            return 0;
        } else if (input == 'q') {
            EngineRuntimeExit(runtime, 0);
        }
    }

    return 1;
}

/*
    If result is non zero, means have some problem.
 */
int SceneStart_DevelopTerminal(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_General(runtime, module_tag, "Entered the scene\n");

    int win_y;
    int win_x;
    getmaxyx(win, win_y, win_x);

    struct WarmTriggerKeyboardCheckEvent key_event;
    TriggerKeyboardCheckEventInit(runtime, &key_event, (int[]){' ', '\n'}, 2, 0);
    TriggerKeyboardCheckEventAppend(runtime, &key_event, (int[]){'q'}, 1, 1);

    struct WarmDialogue2Description event = {
        .attribute = A_NORMAL,
        .position_y = 0,
        .position_x = 0,
        .interval_delay = 16,
    };
    Dialogue2ResetPrintTextEvent(&event);

    event.text = "你好/Hello";
    event.attribute = COLOR_PAIR(1);
    event.type = kDialogueTypeStatic;
    Dialogue2PrintText(runtime, win, &event, NULL);

    event.text = "，在这里可以按 q 键退出（真的？），Enter 或 Space 跳转到下一个对话。";
    event.type = kDialogueTypeWindowReset;
    Dialogue2PrintText(runtime, win, &event, &key_event);

    event.text = "这是关于一个中心句子打印的测试";
    DialoguePrintCenter(runtime, win, &event, &key_event);

    event.text = "This is a Develop Terminal or just a test for a normal example dialogue tree.";
    Dialogue2PrintText(runtime, win, &event, &key_event);

    event.text = "But what's the difference, dialogue trees are just some data structure... We are all normal.";
    Dialogue2PrintText(runtime, win, &event, &key_event);

    event.text = "The protagonist of this program(or videogame), is a shark. But live in another universe.";
    Dialogue2PrintText(runtime, win, &event, &key_event);

    event.text = "沃玛/Warma created him. Maybe his name is littleShark?";
    Dialogue2PrintText(runtime, win, &event, &key_event);

    event.text = "Cute, Evil, Complex, or have another Hidden Story?";
    Dialogue2PrintText(runtime, win, &event, &key_event);

    event.text = "Sorry... But... Can you wait while I continue developing? I need some light ahead of me... also need "
                 "to make with myself.";
    event.type = kDialogueTypeStatic;
    Dialogue2PrintText(runtime, win, &event, NULL);

    struct WarmSelectorActionEvent selector_event[] = {
        {.position_y = win_y * 0.6,
         .position_x = win_x * 0.1,
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .string = "You Idiot"},
        {.position_y = win_y * 0.6,
         .position_x = win_x * 0.5,
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .string = "Take it slow, it's fine"},
    };
    DialogueSelector(runtime, win, selector_event, (sizeof(selector_event) / sizeof(struct WarmSelectorActionEvent)));

    werase(win);
    wrefresh(win);

    TriggerKeyboardCheckEventFreeUp(runtime, &key_event);
    WarmLog_General(runtime, module_tag, "Exit the scene normally\n");
    return 0;
}
