#include "scene/program_info.h"

#include <ncurses.h>

#include "dialogue.h"
#include "log/logger.h"
#include "predefine.h"
#include "runtime.h"

static const char module_tag[] = "Scene.Program-Info";

int SceneStart_ProgramInfo(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_General(runtime, module_tag, "Enter the scene\n");

    // show program info
    werase(win);
    wattron(win, COLOR_PAIR(2));
    wprintw(win, "WarmaShark-Roulette(?)\n");
    wattroff(win, COLOR_PAIR(2));
    wprintw(win, "Made With Open Source Softwares\n");
    wprintw(win, "Version:\t\t%s\n", BUILD_VERSION_STRING);
    wprintw(win, "Git commit:\t\t%s\n", BUILD_GIT_REPO_INFO_STRING);
    wprintw(win, "Build date/time:\t%s\n", BUILD_DATE_STRING);
    wprintw(win, "\n> Press any key to EXIT <\n");
    wrefresh(win);

    // suspend program
    wgetch(win);

    werase(win);
    wrefresh(win);
    WarmLog_General(runtime, module_tag, "Exit the scene\n");

    return 0;
}
