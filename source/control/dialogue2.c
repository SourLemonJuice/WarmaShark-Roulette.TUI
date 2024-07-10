/*
    Dialogue2 is a function based component.
    Different form dialogue1, now the dialogue event don't need to store in an array,
    it self hopes caller config the event just befor calling.

    In short, adjust the event in real time instead of predefined it.
 */

#include "control/dialogue2.h"

#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <ncurses.h>

#include "control/trigger.h"
#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "Control.Dialogue2";

/*
    Note:
        - If key_event is NULL, then skip keyboard check trigger.
 */
int Dialogue2PrintText(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event,
                       struct WarmTriggerKeyboardCheckEvent *key_event)
{
    // print at first
    if (event->interval_delay == 0) {
        // print with attr
        wattron(win, event->attribute);
        wprintw(win, "%s", event->text);
        wattroff(win, event->attribute);
        wrefresh(win);
    } else if (event->interval_delay > 0) {
        wattron(win, event->attribute);
        for (int i = 0; i < strlen(event->text); i++) {
            wprintw(win, "%c", event->text[i]);
            wrefresh(win);
            Dialogue2Delay(runtime, event->interval_delay);
            flushinp();
        }
        wattroff(win, event->attribute);
    } else {
        // TODO
        EngineRuntimeUnload(runtime, 1);
        return 0;
    }

    if (key_event != NULL) {
        TriggerKeyboardCheck(runtime, win, key_event);
    }

    switch (event->type) {
    case kDialogueTypeSentenceEnd:
        Dialogue2Clear(runtime, win, event);
        wmove(win, event->position_y, event->position_x);
        break;
    case kDialogueTypeSentenceEraseWindow:
        werase(win);
        wrefresh(win);
        wmove(win, event->position_y, event->position_x);
        break;
    case kDialogueTypeStatic:
        break;
    }

    if (event->reset_config == true) {
        Dialogue2ResetPrintTextEvent(event);
    }

    return 0;
}

int Dialogue2Delay(struct WarmRuntime *runtime, int length_ms)
{
    struct timespec timespec = {
        .tv_sec = length_ms / 1000,
        .tv_nsec = (length_ms % 1000) * 1000000
    };
    nanosleep(&timespec, NULL);

    return 0;
}

int Dialogue2Clear(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event)
{
    // move to original position
    wmove(win, event->position_y, event->position_x);
    // clear the window
    for (int i = 1; i <= strlen(event->text); i++) {
        wechochar(win, ' '); // echochar() don't need refresh
    }
    // reset position
    wmove(win, event->position_y, event->position_x);

    return 0;
}

/*
    move and take a log

    when using type:static, start position maybe will need to change.
    if what do this, chang the position_* in structure and run this function.
 */
int Dialogue2UpdatePosition(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event)
{
    wmove(win, event->position_y, event->position_x);
    WarmLog_GeneralLn(runtime, module_tag, "position has been updated to: y: %d, x: %d", event->position_y,
                      event->position_x);

    return 0;
}

/*
    don't reset them: {position_*, text}
 */
int Dialogue2ResetPrintTextEvent(struct WarmDialogue2Description *event)
{
    event->type = kDialogueTypeSentenceEnd;
    event->attribute = A_NORMAL;
    event->reset_config = true;

    return 0;
}
