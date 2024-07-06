#ifndef WARM_CONTROL_DIALOGUE2_H_
#define WARM_CONTROL_DIALOGUE2_H_

#include <ncurses.h>

#include "runtime.h"

struct WarmDialogue2Description {
    // cursor position at startup
    // USE: SentencePart, Reset
    int position_y;
    int position_x;
    // what message will be print
    // USE: SentencePart
    char *text;
    // the ncurses print attr
    // USE: SentencePart
    attr_t attribute;
    // TODO speak rate
};

int Dialogue2PrintText(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event);
int Dialogue2Delay(struct WarmRuntime *runtime, WINDOW *win, int length_ms);
int Dialogue2EventClear(struct WarmRuntime *runtime, WINDOW *win, struct WarmDialogue2Description *event);
int Dialogue2EventSetDefaultPrintText(struct WarmDialogue2Description *event);

#endif
