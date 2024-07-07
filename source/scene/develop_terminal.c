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
            EngineRuntimeUnload(runtime, 0);
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

    struct WarmTriggerKeyboardCheckEvent key_event;
    TriggerKeyboardCheckEventInit(runtime, &key_event, (int[]){' ', '\n'}, 2, 0);
    TriggerKeyboardCheckEventAppend(runtime, &key_event, (int[]){'q'}, 1, 1);

    struct WarmDialogue2Description event = {
        .attribute = A_NORMAL,
        .position_y = 0,
        .position_x = 0,
    };

    Dialogue2EventSetDefaultPrintText(&event);
    event.text = "你好/Hello";
    event.attribute = COLOR_PAIR(1);
    Dialogue2PrintText(runtime, win, &event);

    Dialogue2EventSetDefaultPrintText(&event);
    event.text = "，在这里可以按 q 键退出（真的？），Enter 或 Space 跳转到下一个对话。";
    Dialogue2PrintText(runtime, win, &event);
    TriggerKeyboardCheck(runtime, win, &key_event);
    Dialogue2EventClear(runtime, win, &event);

    Dialogue2EventSetDefaultPrintText(&event);
    event.text = "This is a Develop Terminal or just a test for a normal example dialogue tree.";
    Dialogue2PrintText(runtime, win, &event);
    TriggerKeyboardCheck(runtime, win, &key_event);
    Dialogue2EventClear(runtime, win, &event);

    Dialogue2EventSetDefaultPrintText(&event);
    event.text = "But what's the difference, dialogue trees are just some data structure... We are all normal.";
    Dialogue2PrintText(runtime, win, &event);
    TriggerKeyboardCheck(runtime, win, &key_event);
    Dialogue2EventClear(runtime, win, &event);

    Dialogue2EventSetDefaultPrintText(&event);
    event.text = "The protagonist of this program(or videogame), is a shark. But live in another universe.";
    Dialogue2PrintText(runtime, win, &event);
    TriggerKeyboardCheck(runtime, win, &key_event);
    Dialogue2EventClear(runtime, win, &event);

    Dialogue2EventSetDefaultPrintText(&event);
    event.text = "沃玛/Warma created him. Maybe his name is littleShark?";
    Dialogue2PrintText(runtime, win, &event);
    TriggerKeyboardCheck(runtime, win, &key_event);
    Dialogue2EventClear(runtime, win, &event);

    Dialogue2EventSetDefaultPrintText(&event);
    event.text = "Cute, Evil, Complex, or have another Hidden Story?";
    Dialogue2PrintText(runtime, win, &event);
    TriggerKeyboardCheck(runtime, win, &key_event);
    Dialogue2EventClear(runtime, win, &event);

    Dialogue2EventSetDefaultPrintText(&event);
    event.text = "Sorry... But... Can you wait while I continue developing? I need some light ahead of me... also need "
                 "to make with myself.";
    Dialogue2PrintText(runtime, win, &event);
    TriggerKeyboardCheck(runtime, win, &key_event);
    Dialogue2EventClear(runtime, win, &event);

    struct WarmSelectorActionEvent selector_event[] = {
        {.position_y = 0, .position_x = 2, .attribute = A_NORMAL, .attribute_highlight = A_STANDOUT, .string = "Yes"},
        {.position_y = 0, .position_x = 10, .attribute = A_NORMAL, .attribute_highlight = A_STANDOUT, .string = "No"},
    };
    DialogueSelector(runtime, win, selector_event, (sizeof(selector_event) / sizeof(struct WarmSelectorActionEvent)));

    TriggerKeyboardCheckEventFreeUp(runtime, &key_event);
    WarmLog_General(runtime, module_tag, "Exit the scene normally\n");
    return 0;
}
