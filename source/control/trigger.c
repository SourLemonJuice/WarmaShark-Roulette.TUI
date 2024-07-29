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
int TriggerKeyboardCheck(struct WarmRuntime *runtime, WINDOW *win, struct WarmTriggerKeyboardCheckEvent *event)
{
    int input; // it is a char not num
    int result;
    while (true) {
        input = wgetch(win);
        result = TriggerKeyboardCheckExistingKey(runtime, win, event, input);
        if (not(result < 0))
            return result;
    }

    return -1;
}

/*
    Match only one existing key.
 */
int TriggerKeyboardCheckExistingKey(struct WarmRuntime *runtime, WINDOW *win,
                                    struct WarmTriggerKeyboardCheckEvent *event, int key)
{
    struct WarmTriggerKeyboardCheckEvent *current_event = event;
    while (true) {
        if (MatchTheKeys_(key, current_event->keys, current_event->keys_size) == 0)
            return current_event->index;
        // move to next linked list
        // and... the last structure's 'next' is null
        if (current_event->next != NULL) {
            current_event = current_event->next;
            continue;
        } else {
            // if has traversed all structure
            break;
        }
    }

    return -1;
}

int TriggerKeyboardCheckEventInit(struct WarmRuntime *runtime, struct WarmTriggerKeyboardCheckEvent *event, int keys[],
                                  int keys_size, int index)
{
    event->index = index;
    event->keys = keys;
    event->keys_size = keys_size;
    event->next = NULL;

    WarmLog_General(runtime, module_tag, "keyboard event structure has been init\n");
    return 0;
}

/*
    Result:
        0: success
        self exit: there's memory error, so it have right to unload the runtime
 */
int TriggerKeyboardCheckEventAppend(struct WarmRuntime *runtime, struct WarmTriggerKeyboardCheckEvent *event,
                                    int keys[], int keys_size, int index)
{
    struct WarmTriggerKeyboardCheckEvent *last_event = event;
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

    last_event->next = malloc(sizeof(struct WarmTriggerKeyboardCheckEvent));
    if (last_event->next == NULL) {
        return 1;
    }
    last_event->next->keys = keys;
    last_event->next->keys_size = keys_size;
    last_event->next->index = index;
    last_event->next->next = NULL;

    WarmLog_General(runtime, module_tag, "keyboard event linked list has been append\n");
    return 0;
}

int TriggerKeyboardCheckEventFreeUp(struct WarmRuntime *runtime, struct WarmTriggerKeyboardCheckEvent *event)
{
    // the input is a auto storage period, don't free it
    struct WarmTriggerKeyboardCheckEvent *now_ptr = event->next;
    struct WarmTriggerKeyboardCheckEvent *next_ptr;
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
