#ifndef WARM_DIALOGUE_H_
#define WARM_DIALOGUE_H_

#include <stdbool.h>

#include <ncurses.h>

#include "runtime.h"

/*
    The executor will use this enum to ignore the unnecessary part of the event.
    It is also used to specify the behavior, like ...SentencePart will make the executor return a specific value.

    - ...SentencePart: tell caller to continue the next event directly.
    - ...SentenceEnd: the end of this sentence, maybe caller want to suspend program, use with ...Part.
    - ...Delay: just a delay, won't print anything. unit is not determined yet.
 */
enum WarmDialogueEventType {
    kWarmDialogueType_SentencePart,
    kWarmDialogueType_SentenceEnd,
    kWarmDialogueType_Delay,
};

struct WarmDialogueEvent {
    enum WarmDialogueEventType type;
    // what message will be printw()
    char *text;
    // TODO move those comment to type enum
    // is this sentence finished? if `false` will not wait a key and clear the window
    // bool finished;
    // the ncurses print attr
    attr_t attribute;
    // TODO speak rate
};

struct WarmSelectorActionEvent {
    char *string;
    attr_t attribute;
    attr_t attribute_highlight;
    int position_y;
    int position_x;
};

int DialogueExecuteEvent(struct WarmRuntimeConfig *runtime, WINDOW *win, const struct WarmDialogueEvent *event);
int DialogueSelector(struct WarmRuntimeConfig *runtime, WINDOW *win, const struct WarmSelectorActionEvent *event,
                     int event_size);

#endif
