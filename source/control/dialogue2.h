#ifndef WARM_CONTROL_DIALOGUE2_H_
#define WARM_CONTROL_DIALOGUE2_H_

#include <stdbool.h>

#include <ncurses.h>

#include "control/trigger.h"
#include "runtime.h"

/*
    note: the keyboard trigger is a parameter of Dialogue2PrintText(), not a print type
 */
enum WarmDialogue2EventType {
    // clear the printed string(not erase window), and reset position.
    kDialogueTypeSentenceEnd,
    // same like ...SentenceEnd, but will erase the full window.
    // can be used well with ...Static type.
    kDialogueTypeSentenceEraseWindow,
    // don't do anything after print.
    // then no one known the full string length and position, so just erase the window...
    // remember to werase(), even next dialogue may will overwrite the sentence.
    kDialogueTypeStatic,
};

// TODO speak rate
struct WarmDialogue2Description {
    // type
    // default kDialogueTypeSentenceEnd
    enum WarmDialogue2EventType type;
    // cursor position at startup print
    int position_y;
    int position_x;
    // what message will be print
    char *text;
    // the ncurses print attr
    // default: A_NORMAL
    attr_t attribute;
    // reset some config to default after print
    bool reset_config;
};

int Dialogue2PrintText(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event,
                       struct WarmTriggerKeyboardCheckEvent *key_event);
int Dialogue2Delay(struct WarmRuntime *runtime, WINDOW *win, int length_ms);
int Dialogue2Clear(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event);
int Dialogue2UpdatePosition(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event);
int Dialogue2ResetPrintTextEvent(struct WarmDialogue2Description *event);

#endif
