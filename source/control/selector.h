#ifndef WARM_CONTROL_SELECTOR_H_
#define WARM_CONTROL_SELECTOR_H_

#include <stdbool.h>

#include <ncurses.h>

#include "runtime.h"

/*
    TODO Add id system
 */
struct WarmSelectorActionEvent {
    char *string;
    attr_t attribute;
    attr_t attribute_highlight;
    int position_y;
    int position_x;
};

int DialogueSelector(struct WarmRuntime *runtime, WINDOW *win, const struct WarmSelectorActionEvent *event,
                     int event_size);

#endif
