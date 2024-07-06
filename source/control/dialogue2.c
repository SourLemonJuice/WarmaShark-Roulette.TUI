/*
    Dialogue2 is a function based component.
    Different form dialogue1, now the dialogue event don't need to store in an array,
    it self hopes caller config the event just befor calling.

    In short, adjust the event in real time instead of predefined it.
 */

#include "control/dialogue2.h"

#include <string.h>

#include <ncurses.h>

#include "runtime.h"

int Dialogue2PrintText(struct WarmRuntimeConfig *runtime, WINDOW *win, struct WarmDialogue2Description *event)
{
    // print with attr
    wattron(win, event->attribute);
    wprintw(win, "%s", event->text);
    wattroff(win, event->attribute);
    wrefresh(win);

    return 0;
}

int Dialogue2Delay(struct WarmRuntimeConfig *runtime, WINDOW *win, int length_ms)
{
    // TODO
    return 0;
}

int Dialogue2EventClear(struct WarmRuntimeConfig *runtime, WINDOW *win, struct WarmDialogue2Description *event)
{
    // move to original position
    wmove(win, event->position_y, event->position_x);
    // clear the window
    for (int i = 1; i <= strlen(event->text); i++) {
        wechochar(win, ' ');
    }
    // reset position
    wmove(win, event->position_y, event->position_x);

    return 0;
}

// TODO did we really need this? but for future...
int Dialogue2EventSetDefaultPrintText(struct WarmDialogue2Description *event)
{
    event->attribute = A_NORMAL;

    return 0;
}
