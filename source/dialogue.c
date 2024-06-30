#include "dialogue.h"

#include <iso646.h>

#include <ncurses.h>

#include "log/logger.h"
#include "runtime.h"

/*
    Results:
    - 0: A full sentence is finished. And the window has already been erased.
    - 1: Need to continue parsing the next event.
 */
int DialogueExecuteEvent(struct WarmRuntimeConfig *runtime, WINDOW *win, const struct WarmDialogueEvent *event)
{
    // main print
    wattron(win, event->attribute);
    wprintw(win, "%s", event->text);
    wattroff(win, event->attribute);
    wrefresh(win);

    // if the sentence is not finished
    if (event->finished == false) {
        return 1;
    }

    // clear the window
    werase(win);
    // reset to first line
    wmove(win, 0, 0);

    return 0;
}
