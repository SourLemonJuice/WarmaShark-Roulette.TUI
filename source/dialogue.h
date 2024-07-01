#ifndef WARM_DIALOGUE_H_
#define WARM_DIALOGUE_H_

#include <stdbool.h>

#include <ncurses.h>

#include "runtime.h"

struct WarmDialogueEvent {
    // what message will be printw()
    char *text;
    // is this sentence finished? if `false` will not wait a key and clear the window
    bool finished;
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
