#ifndef WARM_CONTROL_TRIGGER_H_
#define WARM_CONTROL_TRIGGER_H_

#include <ncurses.h>

#include "runtime.h"

struct WarmTriggerKeyboardEvent {
    // for result and information for linked list processing
    int index;
    // which key need to detect
    int *keys;
    int keys_size;
    // function will be executed after matching.
    // if is NULL, skip
    void (*action)(void *);
    // parameter of action function.
    // ideally it is a structure, convert type with yourself
    void *action_parma;
    // next linked
    struct WarmTriggerKeyboardEvent *next;
};

int TriggerKeyboardCheck(struct WarmRuntime *runtime, WINDOW *win, struct WarmTriggerKeyboardEvent *event);
int TriggerKeyboardCheckExistingKey(struct WarmRuntime *runtime, WINDOW *win, struct WarmTriggerKeyboardEvent *event,
                                    int key);
struct WarmTriggerKeyboardEvent *TriggerKeyboardCheckEventInit(struct WarmRuntime *runtime, int index, int keys[],
                                                               int keys_size, void (*action)(void *),
                                                               void *action_parma);
int TriggerKeyboardCheckEventAppend(struct WarmRuntime *runtime, struct WarmTriggerKeyboardEvent *event, int index,
                                    int keys[], int keys_size, void (*action)(void *), void *action_parma);
int TriggerKeyboardCheckEventFreeUp(struct WarmRuntime *runtime, struct WarmTriggerKeyboardEvent *event);

#endif
