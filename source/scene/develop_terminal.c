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

static void ExitDueToKeyboard_(void *runtime)
{
    EngineFullExit(runtime, 0);
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

    struct WarmTriggerKeyboardEvent *key_event;
    key_event = TriggerKeyboardCheckEventInit(runtime, 0, (int[]){' ', '\n'}, 2, NULL, NULL);
    TriggerKeyboardCheckEventAppend(runtime, key_event, 1, (int[]){'q'}, 1, ExitDueToKeyboard_, runtime);

    struct DialogueDescription event = {
        .attribute = A_NORMAL,
        .position_y = 0,
        .position_x = 0,
        .interval_delay = 16,
    };
    Dialogue2ResetPrintTextEvent(&event);

    event.text = "你好/Hello";
    event.attribute = COLOR_PAIR(1);
    event.type = kDialogueTypeStatic;
    event.wait_key = false;
    Dialogue2PrintText(runtime, win, &event, key_event);

    event.text = "，在这里可以按 q 键退出（真的可以！），Enter 或 Space 跳转到下一个对话。";
    event.type = kDialogueTypeWindowReset;
    Dialogue2PrintText(runtime, win, &event, key_event);

    event.text = "这是关于一个中心句子打印的测试";
    DialoguePrintCenter(runtime, win, &event, key_event);

    event.text = "This is a Develop Terminal or just a test for a normal example dialogue tree.";
    Dialogue2PrintText(runtime, win, &event, key_event);

    event.text = "But what's the difference, dialogue trees are just some data structure... We are all normal.";
    Dialogue2PrintText(runtime, win, &event, key_event);

    event.text = "The protagonist of this program(or videogame), is a shark. But live in another universe.";
    Dialogue2PrintText(runtime, win, &event, key_event);

    event.text = "沃玛/Warma created him. Maybe his name is littleShark?";
    Dialogue2PrintText(runtime, win, &event, key_event);

    event.text = "Cute, Evil, Complex, or have another Hidden Story?";
    Dialogue2PrintText(runtime, win, &event, key_event);

    event.text = "Sorry... But... Can you wait while I continue developing? I need some light ahead of me... also need "
                 "to make with myself.";
    event.type = kDialogueTypeStatic;
    event.wait_key = false;
    Dialogue2PrintText(runtime, win, &event, key_event);

    struct WarmSelectorActionEvent selector_event[] = {
        {
            .position_y = win_y * 0.6,
            .position_x = win_x * 0.1,
            .attribute = A_NORMAL,
            .attribute_highlight = A_STANDOUT,
            .string = "You Idiot(just joke)",
        },
        {
            .position_y = win_y * 0.6,
            .position_x = win_x * 0.5,
            .attribute = A_NORMAL,
            .attribute_highlight = A_STANDOUT,
            .string = "Take it slow, it's fine",
        },
    };
    DialogueSelector(runtime, win, selector_event, (sizeof(selector_event) / sizeof(struct WarmSelectorActionEvent)));

    DialogueWindowReset(runtime, win, &event);

    TriggerKeyboardCheckEventFreeUp(runtime, key_event);
    werase(win);
    wrefresh(win);
    WarmLog_General(runtime, module_tag, "Exit the scene normally\n");
    return 0;
}
