#include "program_info.h"

#include <ncurses.h>

#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "scene - Program Info";

int SceneStart_ProgramInfo(struct WarmRuntimeConfig *runtime, WINDOW *win)
{
    WarmLog_General(runtime, module_tag, "Enter the scene");

    // show program info
    werase(win);
    wattron(win, COLOR_PAIR(2));
    wprintw(win, "WarmaShark[Under Development]\n");
    wattroff(win, COLOR_PAIR(2));
    wprintw(win, "Made With Open Source Softwares\n");
    wprintw(win, "> Press any key to EXIT <\n");
    wrefresh(win);

    // suspend program
    wgetch(win);

    WarmLog_General(runtime, module_tag, "Exit the scene");

    return 0;
}
