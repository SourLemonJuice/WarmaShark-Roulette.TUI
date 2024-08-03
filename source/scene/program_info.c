#include "scene/program_info.h"

#include <ncurses.h>

#include "control/dialogue2.h"
#include "log/logger.h"
#include "predefine.h"
#include "runtime.h"
#include "window.h"

static const char module_tag[] = "Scene.Program-Info";

int SceneStart_ProgramInfo(struct WarmRuntime *runtime, WINDOW *par_win)
{
    WarmLog_General(runtime, module_tag, "Enter the scene\n");

    WINDOW *win =
        WindowPercentageCreate(runtime, par_win, kWindowTypeHorizontalCenter, 0, kWindowTypeVerticalTop, 0, 1, 0.6);

    // show program info
    werase(win);
    wattron(win, COLOR_PAIR(kColorDangerRed));
    wprintw(win, "WarmaShark-Roulette\n");
    wattroff(win, COLOR_PAIR(kColorDangerRed));
    wprintw(win, "Version:\t\t%s\n", BUILD_VERSION_STRING);
    wprintw(win, "Git commit:\t\t%s\n", BUILD_GIT_REPO_INFO_STRING);
    wprintw(win, "Build date/time:\t%s\n\n", BUILD_DATE_STRING);
    wprintw(win, "2024 酸柠檬猹/SourLemonJuice\n\n");

    PrintwLineCenter(win, "> Press any key to EXIT <");
    wrefresh(win);

    // suspend program
    wgetch(win);

    WarmLog_General(runtime, module_tag, "Exit the scene\n");

    return 0;
}
