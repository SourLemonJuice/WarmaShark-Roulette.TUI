#include "dialogue.h"

#include <iso646.h>
#include <string.h>

#include <ncurses.h>

#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "dialog1 component";

/*
    Results:
    - negative int: Unknown error
    - 0: A full sentence is finished. And the window has already been erased.
    - 1: Need to continue parsing the next event.
 */
int DialogueExecuteEvent(struct WarmRuntime *runtime, WINDOW *win, const struct WarmDialogueEvent *event)
{
    switch (event->type) {
    case kWarmDialogueType_SentencePart:
        // print with attr
        wattron(win, event->attribute);
        wprintw(win, "%s", event->text);
        wattroff(win, event->attribute);
        wrefresh(win);
        return 1;
        break;
    case kWarmDialogueType_SentenceEnd:
        // print with attr
        wattron(win, event->attribute);
        wprintw(win, "%s", event->text);
        wattroff(win, event->attribute);
        wrefresh(win);
        return 0;
        break;
    case kWarmDialogueType_Delay:
        return 1;
        break;
    }

    // unknown issue
    return -1;
}
