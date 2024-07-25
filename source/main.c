#include <iso646.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "control/dialogue2.h"
#include "control/selector.h"
#include "log/logger.h"
#include "runtime.h"
#include "scene/scene_collection.h"
#include "window.h"

static const char module_tag[] = "Main";

int main(int argc, char *argv[])
{
    // init program
    struct WarmRuntime runtime;
    EngineRuntimeInit(&runtime);

    WarmLog_GeneralLn(&runtime, module_tag, "Starting processing command flags");
    // handle command arguments
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0) {
                printf("Usage: executable [--help] [--version]\n");
                printf("It's a TUI game, build with ncurses.\n");
                EngineRuntimeUnload(&runtime);
                exit(0);
            } else if (strcmp(argv[i], "--version") == 0) {
                EngineNcursesInit(&runtime);
                SceneStart_ProgramInfo(&runtime, stdscr);
                EngineRuntimeExit(&runtime, 0);
            } else {
                printf("Error: Invalid arguments '%s', use '--help' to see more info.\n", argv[i]);
                EngineRuntimeUnload(&runtime);
                exit(1);
            }
        }
    }
    EngineNcursesInit(&runtime);

    // record some information for tracking
    WarmLog_GeneralLn(&runtime, module_tag, "Program locale should have been set to '%s'", runtime.locale_string);
    WarmLog_GeneralLn(&runtime, module_tag, "MAX screen X: %d, Y: %d", runtime.terminal_x, runtime.terminal_y);
    WarmLog_GeneralLn(&runtime, module_tag, "program runtime has been init, starting scene selector");

    // select the scene
    wprintw(stdscr, "Choose the scene(For Develop):");
    struct WarmSelectorActionEvent scene_selector_event[] = {
        {.string = "Quit/Exit",
         .attribute = A_DIM,
         .attribute_highlight = A_STANDOUT,
         .position_y = 1,
         .position_x = 2},
        {.string = "Develop Terminal\t[Little Dialogue Demo]",
         .attribute = A_DIM,
         .attribute_highlight = A_STANDOUT,
         .position_y = 2,
         .position_x = 2},
        {.string = "Program info\t\t[Build Version]",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 3,
         .position_x = 2},
        {.string = "Shark Roulette\t[Main Game]",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 4,
         .position_x = 2},
        {.string = "Selector Show/Test\t[Just for Test]",
         .attribute = A_DIM,
         .attribute_highlight = A_STANDOUT,
         .position_y = 5,
         .position_x = 2},
    };
    int selected_scene = DialogueSelector(&runtime, stdscr, scene_selector_event, 5);
    werase(stdscr);

    WINDOW *window; // for upcoming scene
    switch (selected_scene) {
    case 0:
        // quit program
        EngineRuntimeExit(&runtime, 0);
        break;
    case 1:
        // scene - develop terminal
        PrintwLineCenter(stdscr, "Yeah, welcome to WarmaShark, below is the develop terminal.\n");
        PrintwLineCenter(stdscr, "======== ======== ======== ======== ======== ======== ========\n");
        wrefresh(stdscr);

        // create a window for the border of develop terminal scene
        window = WindowPercentageCreate(&runtime, stdscr, kWindowTypeHorizontalCenter, 0, kWindowTypeVerticalTop, 2,
                                        0.4, 0.7);
        window = WindowEngravedBorder(&runtime, window);

        SceneStart_DevelopTerminal(&runtime, window);
        break;
    case 2:
        // scene - program info
        SceneStart_ProgramInfo(&runtime, stdscr);
        break;
    case 3:
        // Shark Roulette
        wprintw(stdscr, "Little Shark Roulette\n");
        wrefresh(stdscr);

        window = newwin((runtime.terminal_y - 1) * 0.7, runtime.terminal_x * 0.7, 1, 4);
        window = WindowEngravedBorder(&runtime, window);

        SceneStart_SharkRoulette(&runtime, window);
        break;
    case 4:
        // Selector Show/Test
        SceneStart_SelectorShow(&runtime, stdscr);
        break;
    }

    // free up everything
    EngineRuntimeExit(&runtime, 0);

    return 0;
}
