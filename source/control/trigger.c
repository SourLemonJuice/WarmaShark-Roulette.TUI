#include "control/trigger.h"

#include <iso646.h>
#include <stdbool.h>
#include <stdlib.h>

#include <ncurses.h>

#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "Control.Trigger";

/*
    Results:
        0: matched
        1: then not
 */
static int MatchTheKeys_(int input, int target[], int size)
{
    for (int i = 0; i < size; i++) {
        if (input == target[i]) {
            return 0;
        }
    }
    return 1;
}

/*
    Results:
        negative num: have error
        positive num: key index
 */
int TriggerKeyboardCheck(struct WarmRuntime *runtime, WINDOW *win, struct WarmTriggerKeyboardEvent *event)
{
    int input; // it is a char not num
    int result;
    while (true) {
        input = wgetch(win);
        result = TriggerKeyboardCheckExistingKey(runtime, win, event, input);
        if (result >= 0)
            return result;
    }

    return -1;
}

/*
    Match only one existing key.
 */
int TriggerKeyboardCheckExistingKey(struct WarmRuntime *runtime, WINDOW *win, struct WarmTriggerKeyboardEvent *event,
                                    int key)
{
    struct WarmTriggerKeyboardEvent *current = event; // the current event
    while (true) {
        if (MatchTheKeys_(key, current->keys, current->keys_size) == 0) {
            if (current->action != NULL)
                current->action(current->action_parma);
            return current->index;
        }
        // move to next linked list
        // and... the last structure's 'next' is null
        if (current->next != NULL) {
            current = current->next;
            continue;
        } else {
            // if has traversed all structure
            break;
        }
    }

    return -1;
}

struct WarmTriggerKeyboardEvent *TriggerKeyboardCheckEventInit(struct WarmRuntime *runtime, int index, int keys[],
                                                               int keys_size, void (*action)(void *),
                                                               void *action_parma)
{
    struct WarmTriggerKeyboardEvent *event = malloc(sizeof(struct WarmTriggerKeyboardEvent));

    event->keys = keys;
    event->keys_size = keys_size;
    event->action = action;
    event->action_parma = action_parma;
    event->index = index;
    event->next = NULL;

    WarmLog_General(runtime, module_tag, "keyboard event structure has been init\n");
    return event;
}

/*
    Result:
        0: success
        self exit: there's memory error, so it have right to unload the runtime
 */
int TriggerKeyboardCheckEventAppend(struct WarmRuntime *runtime, struct WarmTriggerKeyboardEvent *event, int index,
                                    int keys[], int keys_size, void (*action)(void *), void *action_parma)
{
    struct WarmTriggerKeyboardEvent *last_event = event;
    while (true) {
        // if already have a event have the same index, return a error
        if (last_event->index == index) {
            WarmthMeltdownUniverse(runtime, "try to append a existing keyboard event index\n");
        }
        if (last_event->next != NULL) {
            last_event = last_event->next;
        } else {
            break;
        }
    }
    // last_event has been found

    last_event->next = malloc(sizeof(struct WarmTriggerKeyboardEvent));
    if (last_event->next == NULL) {
        return 1;
    }
    last_event->next->keys = keys;
    last_event->next->keys_size = keys_size;
    last_event->next->action = action;
    last_event->next->action_parma = action_parma;
    last_event->next->index = index;
    last_event->next->next = NULL;

    WarmLog_General(runtime, module_tag, "keyboard event linked list has been append\n");
    return 0;
}

int TriggerKeyboardCheckEventFreeUp(struct WarmRuntime *runtime, struct WarmTriggerKeyboardEvent *event)
{
    // the old input is a auto storage period, don't free it.
    // but new design hope it's in heap memory, free up it now
    struct WarmTriggerKeyboardEvent *now_ptr = event;
    struct WarmTriggerKeyboardEvent *next_ptr;
    while (true) {
        next_ptr = now_ptr->next; // record next struct, even though it is NULL
        free(now_ptr);
        // if we don't have next struct, the work is over
        if (next_ptr == NULL) {
            break;
        } else {
            now_ptr = next_ptr;
        }
    }

    return 0;
}
