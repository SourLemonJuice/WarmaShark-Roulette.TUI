#include "dialogue.h"

#include <iso646.h>
#include <string.h>

#include <ncurses.h>

#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "dialog component";

/*
    Results:
    - negative int: Unknown error
    - 0: A full sentence is finished. And the window has already been erased.
    - 1: Need to continue parsing the next event.
 */
int DialogueExecuteEvent(struct WarmRuntimeConfig *runtime, WINDOW *win, const struct WarmDialogueEvent *event)
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

/*
    Refresh specified event object.
    The old one will be set to normal attr, the new one will be set to highlight attr.
    If the old one is a negative, then skip its update.
 */
static int DialogueSelectorUpdateStatus_(struct WarmRuntimeConfig *runtime, WINDOW *win,
                                         const struct WarmSelectorActionEvent *event, int old, int new)
{
    WarmLog_General(runtime, module_tag, "update selector view(old->new): %d->%d\n", old, new);

    // set old enter to normal attr
    if (old >= 0) {
        wattron(win, event[old].attribute);
        wmove(win, event[old].position_y, event[old].position_x);
        wprintw(win, "%s", event[old].string);
        wattroff(win, event[old].attribute);
    }
    // the new enter to highlight attr
    wattron(win, event[new].attribute_highlight);
    wmove(win, event[new].position_y, event[new].position_x);
    wprintw(win, "%s", event[new].string);
    wattroff(win, event[new].attribute_highlight);
    // finale refresh
    wrefresh(win);

    return 0;
}

/*
    Clear all objects on the screen
 */
static int DialogueSelectorClearOptionsOnScreen_(struct WarmRuntimeConfig *runtime, WINDOW *win,
                                                 const struct WarmSelectorActionEvent *event, int event_size)
{
    WarmLog_General(runtime, module_tag, "Clearing selector options on screen\n");

    wattrset(win, A_NORMAL);
    for (int i = 0; i < event_size; i++) {
        wmove(win, event[i].position_y, event[i].position_x);
        for (int ii = 0; ii <= strlen(event[i].string); ii++) {
            waddch(win, ' ');
        }
    }
    return 0;
}

int DialogueSelector(struct WarmRuntimeConfig *runtime, WINDOW *win, const struct WarmSelectorActionEvent *event,
                     int event_size)
{
    // this func need get arrow key... so force enable keypad()
    keypad(win, true);

    // get source position, for later recovery
    int source_y;
    int source_x;
    getyx(win, source_y, source_x);

    int selecting = 0;
    int pre_selecting = 0;
    int key;

    for (int i = 0; i < event_size; i++) {
        wattron(win, event[i].attribute);
        wmove(win, event[i].position_y, event[i].position_x);
        wprintw(win, "%s", event[i].string);
        wattroff(win, event[i].attribute);
    }
    // finished init
    wrefresh(win);
    // highlight default enter
    DialogueSelectorUpdateStatus_(runtime, win, event, -1, selecting);

    while (true) {
        key = wgetch(win);
        if (key == KEY_DOWN or key == KEY_RIGHT) {
            pre_selecting = selecting + 1;
            if (pre_selecting < event_size and pre_selecting >= 0) {
                DialogueSelectorUpdateStatus_(runtime, win, event, selecting, pre_selecting);
                selecting = pre_selecting;
            }
        }
        if (key == KEY_UP or key == KEY_LEFT) {
            pre_selecting = selecting - 1;
            if (pre_selecting < event_size and pre_selecting >= 0) {
                DialogueSelectorUpdateStatus_(runtime, win, event, selecting, pre_selecting);
                selecting = pre_selecting;
            }
        }
        // the finale return, remember to reset the position
        if (key == '\n') {
            DialogueSelectorClearOptionsOnScreen_(runtime, win, event, event_size);
            wmove(win, source_y, source_x);
            return selecting;
        }
    }

    return 0;
}
