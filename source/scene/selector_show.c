#include "selector_show.h"

#include <ncurses.h>

#include "control/selector.h"
#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "scene - selector show";

int SceneStart_SelectorShow(struct WarmRuntimeConfig *runtime, WINDOW *win)
{
    wprintw(win, "Here is a selector test\n");
    struct WarmSelectorActionEvent selector_event[] = {
        {.string = "test1",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 1,
         .position_x = 1},
        {.string = "test2",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 2,
         .position_x = 2},
        {.string = "Hello World 3",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 2,
         .position_x = 16},
        {.string = "Still useless",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 3,
         .position_x = 0},
    };
    int result = DialogueSelector(runtime, win, selector_event, 4);
    WarmLog_General(runtime, module_tag, "selector result %d\n", result);

    wprintw(win, "The result index is: %d\n", result);
    wrefresh(win);
    wgetch(win);

    werase(win);
    wprintw(win, "[The selected index is: %d]\n", result);
    wrefresh(win);

    return 0;
}
