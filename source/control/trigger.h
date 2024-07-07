#ifndef WARM_CONTROL_TRIGGER_H_
#define WARM_CONTROL_TRIGGER_H_

#include <ncurses.h>

#include "runtime.h"

struct WarmTriggerKeyboardCheckEvent {
    // for result and information for linked list processing
    int index;
    // which key need to detect
    int *keys;
    int keys_size;
    // next linked
    struct WarmTriggerKeyboardCheckEvent *next;
};

int TriggerKeyboardCheck(struct WarmRuntime *runtime, WINDOW *win, struct WarmTriggerKeyboardCheckEvent *event);
int TriggerKeyboardCheckEventInit(struct WarmRuntime *runtime, struct WarmTriggerKeyboardCheckEvent *event, int keys[],
                                  int keys_size, int index);
int TriggerKeyboardCheckEventAppend(struct WarmRuntime *runtime, struct WarmTriggerKeyboardCheckEvent *event,
                                    int keys[], int keys_size, int index);
int TriggerKeyboardCheckEventFreeUp(struct WarmRuntime *runtime, struct WarmTriggerKeyboardCheckEvent *event);

#endif
