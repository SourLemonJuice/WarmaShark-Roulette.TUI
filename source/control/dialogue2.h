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
    // don't do anything after print.
    // then no one known the full string length and position, so just erase the window...
    // remember to werase(), even next dialogue may will overwrite the sentence.
    kDialogueTypeStatic,
    // same like ...SentenceEnd, but will erase the full window.
    // can be used well with ...Static type.
    // put it on the last event before it need to be cleared.
    kDialogueTypeWindowReset,
};

struct DialogueDescription {
    // type
    // default: kDialogueTypeSentenceEnd
    enum WarmDialogue2EventType type;
    // cursor position at startup print
    // default: won't set
    int position_y;
    int position_x;
    // what message will be print
    // default: won't set
    char *text;
    // the ncurses print attr
    // default: A_NORMAL
    attr_t attribute;
    // speak rate(ms). 0 is disable
    // default: won't set
    int interval_delay;
    // fast mode status, if true ignore the speak rate(interval_delay)
    bool fast_sentence;
    // wait a key trigger event after print. it's not a print detection, that's controlled by skip_sentence
    bool wait_key;
    // reset some config in structure to default after print
    // default: true
    bool reset_config;
};

int Dialogue2PrintText(struct WarmRuntime *runtime, WINDOW *win, struct DialogueDescription *event,
                       struct WarmTriggerKeyboardCheckEvent *key_event);
int DialoguePrintCenter(struct WarmRuntime *runtime, WINDOW *win, struct DialogueDescription *event,
                        struct WarmTriggerKeyboardCheckEvent *key_event);
int DialogueWindowReset(struct WarmRuntime *runtime, WINDOW *win, struct DialogueDescription *event);
int DialogueDelay(struct WarmRuntime *runtime, int length_ms);
int DialogueClear(struct WarmRuntime *runtime, WINDOW *win, struct DialogueDescription *event);
// int Dialogue2UpdatePosition(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event);
int Dialogue2ResetPrintTextEvent(struct DialogueDescription *event);

#endif
