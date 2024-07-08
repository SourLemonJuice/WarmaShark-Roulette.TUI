#ifndef WARM_CONTROL_DIALOGUE2_H_
#define WARM_CONTROL_DIALOGUE2_H_

#include <stdbool.h>

#include <ncurses.h>

#include "control/trigger.h"
#include "runtime.h"

// TODO speak rate
struct WarmDialogue2Description {
    // reset some config to default after print
    bool reset_config;
    // cursor position at startup
    int position_y;
    int position_x;
    // what message will be print
    char *text;
    // the ncurses print attr
    // default: A_NORMAL
    attr_t attribute;
    // clear after printing
    // default: true
    bool clear;
    // reset position after print
    // default: true
    bool reset_position;
};

int Dialogue2PrintText(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event,
                       struct WarmTriggerKeyboardCheckEvent *key_event);
int Dialogue2Delay(struct WarmRuntime *runtime, WINDOW *win, int length_ms);
int Dialogue2Clear(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event);
int Dialogue2UpdatePosition(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event);
int Dialogue2EventSetDefaultPrintText(struct WarmDialogue2Description *event);

#endif
