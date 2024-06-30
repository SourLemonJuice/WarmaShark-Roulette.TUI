#ifndef WARM_DIALOGUE_H_
#define WARM_DIALOGUE_H_

#include <stdbool.h>

#include <ncurses.h>

#include "runtime.h"

struct WarmDialogueEvent {
    // what message will be printw()
    char *text;
    // is this sentence finished? if `flase` will not wait a key and clear the window
    bool finished;
    // the ncurses print attr
    int attribute;
    // TODO speak rate
};

int DialogueExecuteEvent(struct WarmRuntimeConfig *runtime, WINDOW *win, const struct WarmDialogueEvent *event);

#endif
