/*
    Dialogue2 is a function based component.
    Different form dialogue1, now the dialogue event don't need to store in an array,
    it self hopes caller config the event just befor calling.

    In short, adjust the event in real time instead of predefined it.
 */

#include "control/dialogue2.h"

#include <iso646.h>
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
    Main print function.
    Note:
        - If text is NULL, skip the text print.
          It's useful if only want to use kDialogueTypeWindowReset.
        - [removed] If key_event is NULL, then skip keyboard check trigger.
        - When function returned, the cursor won't be reset to origin.
 */
int Dialogue2PrintText(struct WarmRuntime *runtime, WINDOW *win, struct DialogueDescription *event,
                       struct WarmTriggerKeyboardCheckEvent *key_event)
{
    // move at first
    wmove(win, event->position_y, event->position_x);

    // then start to print
    if (event->text == NULL) {
        // skip the print
    } else if (event->interval_delay == 0 or event->fast_sentence == true) {
        // print, with attr
        wattron(win, event->attribute);
        wprintw(win, "%s", event->text);
        wattroff(win, event->attribute);
        wrefresh(win);
    } else if (event->interval_delay > 0) {
        // use getch() with wtimeout() in cbreak() mode to implement speak rate
        wtimeout(win, event->interval_delay);
        int input; // temp char
        // print, with attr and speak rate
        wattron(win, event->attribute);
        for (int i = 0; i < strlen(event->text); i++) {
            wprintw(win, "%c", event->text[i]);
            wrefresh(win);
            input = wgetch(win);
            if (input == ERR) {
                continue;
            } else if (TriggerKeyboardCheckExistingKey(runtime, win, key_event, input) >= 0) {
                // set this flag
                event->fast_sentence = true;
                // display the full sentence immediately
                wmove(win, event->position_y, event->position_x);
                wprintw(win, "%s", event->text);
                break;
            }
        }
        wattroff(win, event->attribute);
        wtimeout(win, 0);
    } else {
        WarmthMeltdownUniverse(runtime, "Dialogue2 PrintText event have a invalid value of 'interval_delay'\n");
        return 0;
    }

    if (event->wait_key == true)
        TriggerKeyboardCheck(runtime, win, key_event);

    switch (event->type) {
    case kDialogueTypeSentenceEnd:
        DialogueClear(runtime, win, event);
        event->fast_sentence = false; // off skip mode
        break;
    case kDialogueTypeStatic:
        // keep the content, update position to current
        getyx(win, event->position_y, event->position_x);
        break;
    case kDialogueTypeWindowReset:
        // erase the window
        werase(win);
        wrefresh(win);
        // reset the position to origin of window
        event->position_y = 0;
        event->position_x = 0;
        event->fast_sentence = false; // off skip mode
        break;
    default:
        WarmLog_WarningLn(runtime, module_tag, "Dialogue2PrintText unknown event type");
        break;
    }

    if (event->reset_config == true)
        Dialogue2ResetPrintTextEvent(event);

    return 0;
}

/*
    Print sentence in center of x-axis. The y-axis uses event position.
    It looked may not great yet, but I'll improve them... I think?
 */
int DialoguePrintCenter(struct WarmRuntime *runtime, WINDOW *win, struct DialogueDescription *event,
                        struct WarmTriggerKeyboardCheckEvent *key_event)
{
    int max_y;
    int max_x;
    getmaxyx(win, max_y, max_x);
    int str_len = strlen(event->text);

    // dump source position
    int src_pos_y = event->position_y;
    int src_pos_x = event->position_x;

    event->position_x = (max_x - str_len) / 2;

    // the max_x is a limit, don't try to exceed it.
    if (max_x > str_len)
        wmove(win, event->position_y, event->position_x);
    else
        wmove(win, event->position_y, 0);

    // and using the normal print function, which may be changed later
    Dialogue2PrintText(runtime, win, event, key_event);

    // reset position
    event->position_y = src_pos_y;
    event->position_x = src_pos_x;

    return 0;
}

/*
    Delay in ms.
 */
int DialogueDelay(struct WarmRuntime *runtime, int length_ms)
{
    struct timespec timespec = {
        .tv_sec = length_ms / 1000,
        .tv_nsec = (length_ms % 1000) * 1000000,
    };
    nanosleep(&timespec, NULL);

    return 0;
}

/*
    Use blank characters replace the event string.
    But won't chang other things.
 */
int DialogueClear(struct WarmRuntime *runtime, WINDOW *win, struct DialogueDescription *event)
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
    [try to remove]
    move and take a log

    when using kDialogueTypeStatic, start position maybe will need to change.
    if what do this, chang the position_* in structure and run this function.
 */
int Dialogue2UpdatePosition(struct WarmRuntime *runtime, WINDOW *win, struct DialogueDescription *event)
{
    wmove(win, event->position_y, event->position_x);
    WarmLog_GeneralLn(runtime, module_tag, "position has been updated to: y: %d, x: %d", event->position_y,
                      event->position_x);

    return 0;
}

/*
    Init WarmDialogue2Description structure.
 */
int DialogueDescriptionInit(struct DialogueDescription *event)
{
    event->type = kDialogueTypeSentenceEnd;
    event->position_y = 0;
    event->position_x = 0;
    event->text = NULL;
    event->attribute = A_NORMAL;
    event->interval_delay = 16;
    event->fast_sentence = false;
    event->wait_key = true;
    event->reset_config = true;

    return 0;
}

/*
    Won't reset them: {position_*, text}
 */
int Dialogue2ResetPrintTextEvent(struct DialogueDescription *event)
{
    event->type = kDialogueTypeSentenceEnd;
    event->attribute = A_NORMAL;
    event->reset_config = true;
    event->wait_key = true;

    return 0;
}
