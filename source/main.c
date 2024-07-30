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

enum WarmProgramMainAction {
    kWarmProgramActionHelpInfo,
    kWarmProgramActionVersionScene,
    kWarmProgramActionSceneSelection,
};

static int SelectionSceneMain_(struct WarmRuntime *runtime)
{
    wprintw(stdscr, "Choose the scene:");
    struct WarmSelectorActionEvent scene_selector_event[] = {
        {.string = "Quit/Exit",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 1,
         .position_x = 2},
        {.string = "Develop Tool Box\t[Develop]",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 2,
         .position_x = 2},
        {.string = "Shark Roulette\t[Main Game]",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 3,
         .position_x = 2},
    };
    int selected_scene = DialogueSelector(runtime, stdscr, scene_selector_event,
                                          sizeof(scene_selector_event) / sizeof(struct WarmSelectorActionEvent));
    werase(stdscr);
    wrefresh(stdscr);

    return selected_scene;
}

static int SelectionSceneDevelop_(struct WarmRuntime *runtime)
{
    wprintw(stdscr, "Develop Tool Box:");
    struct WarmSelectorActionEvent selector_event[] = {
        {.string = "Develop Terminal\t[Little Dialogue Demo]",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 1,
         .position_x = 2},
        {.string = "Program info\t\t[Build Version]",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 2,
         .position_x = 2},
        {.string = "Selector Show/Test\t[Just for Test]",
         .attribute = A_DIM,
         .attribute_highlight = A_STANDOUT,
         .position_y = 3,
         .position_x = 2},
    };
    int selected = DialogueSelector(runtime, stdscr, selector_event,
                                    sizeof(selector_event) / sizeof(struct WarmSelectorActionEvent));
    werase(stdscr);
    wrefresh(stdscr);

    return selected;
}

int main(int argc, char *argv[])
{
    // init runtime
    struct WarmRuntime runtime;
    EngineRuntimeInit(&runtime);

    // default action is SceneSelection
    enum WarmProgramMainAction program_action = kWarmProgramActionSceneSelection;
    // handle command arguments
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0 or strcmp(argv[i], "-h") == 0) {
                // show help info
                program_action = kWarmProgramActionHelpInfo;
            } else if (strcmp(argv[i], "--version") == 0) {
                // open version scene
                program_action = kWarmProgramActionVersionScene;
            } else if (strcmp(argv[i], "--logging") == 0) {
                // enable log
                runtime.logging = true;
            } else if (strcmp(argv[i], "--log-path") == 0) {
                // set log file path
                i++;
                if (i >= argc) {
                    printf("Error: No value of flag '--log-path'\n");
                    exit(kWarmErrorFlagProcess);
                }
                runtime.log_path = argv[i];
            } else {
                printf("Error: Invalid arguments '%s', use '--help' to see more info.\n", argv[i]);
                exit(kWarmErrorFlagProcess);
            }
        }
    }

    switch (program_action) {
    case kWarmProgramActionHelpInfo:
        printf("Usage: Executable-File [--help | -h] [--version] [--logging] [--log-path <path>]\n\n");
        printf("It's a full-screen TUI game, build with Ncurses. Try to run it without flags.\n");
        printf("The default log path is \"./Engine.log\", use \"--logging\" to enable it, or \"--log-path\" to change "
               "it.\n");
        exit(EXIT_SUCCESS);
        break;
    case kWarmProgramActionVersionScene:
        EngineNcursesInit(&runtime);
        EngineLogSystemInit(&runtime);
        SceneStart_ProgramInfo(&runtime, stdscr);
        EngineFullExit(&runtime, EXIT_SUCCESS);
        break;
    case kWarmProgramActionSceneSelection:
        EngineLogSystemInit(&runtime);
        EngineNcursesInit(&runtime);
        break;
    default:
        printf("Error: Unimplemented type of enum WarmProgramMainAction");
        exit(kWarmErrorFlagProcess);
        break;
    }

    // record some information for tracking
    WarmLog_GeneralLn(&runtime, module_tag, "Program locale should have been set to '%s'", runtime.locale_string);
    WarmLog_GeneralLn(&runtime, module_tag, "MAX screen X: %d, Y: %d", runtime.terminal_x, runtime.terminal_y);
    WarmLog_GeneralLn(&runtime, module_tag, "program runtime has been init, starting scene selector");

    // select the scene
    int selected_scene = SelectionSceneMain_(&runtime);

    WINDOW *window; // for upcoming scene
    switch (selected_scene) {
    case 0:
        // quit program
        EngineFullExit(&runtime, 0);
        break;
    case 1:
        selected_scene = SelectionSceneDevelop_(&runtime);
        switch (selected_scene) {
        case 0:
            // scene - develop terminal
            PrintwLineCenter(stdscr, "Yeah, welcome to WarmaShark, below is the develop terminal.\n");
            PrintwLineCenter(stdscr, "======== ======== ======== ======== ======== ======== ======== ========\n");
            wrefresh(stdscr);

            // create a window for the border of develop terminal scene
            window = WindowPercentageCreate(&runtime, stdscr, kWindowTypeHorizontalCenter, 0, kWindowTypeVerticalTop, 2,
                                            0.4, 0.7);
            window = WindowEngravedBorder(&runtime, window);

            SceneStart_DevelopTerminal(&runtime, window);
            break;
        case 1:
            // scene - program info
            SceneStart_ProgramInfo(&runtime, stdscr);
            break;
        case 2:
            // Selector Show/Test
            SceneStart_SelectorShow(&runtime, stdscr);
            break;
        }
        break;
    case 2:
        // Shark Roulette
        PrintwLineCenter(stdscr, "Little Shark Roulette\n");
        wrefresh(stdscr);

        window = WindowPercentageCreate(&runtime, stdscr, kWindowTypeHorizontalCenter, 0, kWindowTypeVerticalTop, 1,
                                        0.55, 0.8);
        window = WindowEngravedBorder(&runtime, window);

        SceneStart_SharkRoulette(&runtime, window);
        werase(stdscr);
        wrefresh(stdscr);
        SceneStart_ProgramInfo(&runtime, stdscr);
        break;
    }

    // free up everything
    EngineFullExit(&runtime, EXIT_SUCCESS);

    return 0;
}
