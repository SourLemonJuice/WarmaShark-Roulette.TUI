#include "control/trigger.h"

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
    struct WarmTriggerKeyboardCheckEvent *current_event = event;
    while (true) {
        input = wgetch(win);
        while (true) {
            if (MatchTheKeys_(input, current_event->keys, current_event->keys_size) == 0) {
                return current_event->index;
            }
            // move to next linked list
            // and... the last structure's 'next' is null
            if (current_event->next != NULL) {
                current_event = current_event->next;
                continue;
            } else {
                break;
            }
        }
    }

    return 0;
}

int TriggerKeyboardCheckEventInit(struct WarmRuntime *runtime, struct WarmTriggerKeyboardCheckEvent *event, int keys[],
                                  int keys_size, int index)
{
    event->index = index;
    event->keys = keys;
    event->keys_size = keys_size;
    event->next = NULL;
    return 0;
}

int TriggerKeyboardCheckEventAppend(struct WarmRuntime *runtime, struct WarmTriggerKeyboardCheckEvent *event,
                                    int keys[], int keys_size, int index)
{
    struct WarmTriggerKeyboardCheckEvent *last_event = event;
    while (true) {
        if (last_event->next != NULL) {
            last_event = last_event->next;
        } else {
            break;
        }
    }
    // last_event has been init

    WarmLog_General(runtime, module_tag, "last_event->next is: %p, index: %d\n", last_event->next, last_event->index);
    last_event->next = malloc(sizeof(struct WarmTriggerKeyboardCheckEvent));
    if (last_event->next == NULL) {
        return 1;
    }
    last_event->next->keys = keys;
    last_event->next->keys_size = keys_size;
    last_event->next->index = index;
    last_event->next->next = NULL;

    WarmLog_General(runtime, module_tag, "event linked list has been append\n");
    return 0;
}
