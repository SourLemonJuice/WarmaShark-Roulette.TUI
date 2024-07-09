#include <iso646.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "control/selector.h"
#include "log/logger.h"
#include "runtime.h"
#include "scene/scene_collection.h"

static const char module_tag[] = "Main";

int main(int argc, char *argv[])
{
    // init program
    struct WarmRuntime runtime;
    EngineRuntimeInit(&runtime);

    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // handle command arguments
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0) {
                endwin();
                printf("Usage: executable [--help] [--version]\n");
                printf("This is a game, build with ncurses.\n");
                EngineRuntimeUnload(&runtime, 0);
            } else if (strcmp(argv[i], "--version") == 0) {
                SceneStart_ProgramInfo(&runtime, stdscr);
                EngineRuntimeUnload(&runtime, 0);
            } else {
                endwin();
                printf("ERROR: Invalid arguments '%s'\n", argv[i]);
                EngineRuntimeUnload(&runtime, 1);
            }
        }
    }

    // record some information for tracking
    WarmLog_GeneralLn(&runtime, module_tag, "Program locale should have been set to %s", runtime.locale_string);
    WarmLog_GeneralLn(&runtime, module_tag, "MAX screen X: %d, Y: %d", runtime.terminal_x, runtime.terminal_y);
    WarmLog_GeneralLn(&runtime, module_tag, "program runtime has been init, starting scene selector");

    // select the scene
    wprintw(stdscr, "Choose the scene(For Develop):");
    struct WarmSelectorActionEvent scene_selector_event[] = {
        {.string = "Quit Program",
         .attribute = A_DIM,
         .attribute_highlight = A_STANDOUT,
         .position_y = 1,
         .position_x = 2},
        {.string = "Develop Terminal",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 2,
         .position_x = 2},
        {.string = "Program info",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 3,
         .position_x = 2},
        {.string = "Shark Roulette",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 4,
         .position_x = 2},
        {.string = "Selector Show/Test",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 5,
         .position_x = 2},
    };
    int selected_scene = DialogueSelector(&runtime, stdscr, scene_selector_event, 5);
    werase(stdscr);

    switch (selected_scene) {
    case 0:
        // quit program
        EngineRuntimeUnload(&runtime, 0);
        break;
    case 1:
        // scene - develop terminal
        attron(COLOR_PAIR(1));
        wprintw(stdscr, "Yeah,");
        attroff(COLOR_PAIR(1));
        wprintw(stdscr, " Welcome to WarmaShark, below is the develop terminal.\n");
        wprintw(stdscr, "======== ======== ======== ======== ========\n");
        wrefresh(stdscr);

        // create a window for the border of develop terminal scene
        WINDOW *window = newwin((runtime.terminal_y - 2) * 0.4, runtime.terminal_x * 0.7, 2, 0);
        box(window, 0, 0);
        wrefresh(window);

        // creat a new windows without border
        delwin(window);
        window = newwin(((runtime.terminal_y - 2) * 0.4) - 2, (runtime.terminal_x * 0.7) - 2, 3, 1);
        // start test scene
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
        WINDOW *win = newwin((runtime.terminal_y - 1) * 0.4, runtime.terminal_x * 0.7, 1, 0);
        box(win, 0, 0);
        wrefresh(win);
        delwin(win);
        win = newwin((runtime.terminal_y - 1) * 0.4 - 2, runtime.terminal_x * 0.7 - 2, 2, 1);
        StartScene_SharkRoulette(&runtime, win);
        break;
    case 4:
        // Selector Show/Test
        SceneStart_SelectorShow(&runtime, stdscr);
        break;
    }

    // free up everything
    EngineRuntimeUnload(&runtime, 0);

    return 0;
}
