#include <iso646.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "dialogue.h"
#include "log/logger.h"
#include "runtime.h"
#include "scene/develop_terminal.h"
#include "scene/program_info.h"

int main(int argc, char *argv[])
{
    // init engine
    struct WarmRuntimeConfig runtime_config;
    EngineRuntimeInit(&runtime_config);

    // if have any arguments, then break program
    if (argc >= 2) {
        WarmLog_Warning(&runtime_config, "main", "there is a CLI argument input here, we don't use it\n");
    }

    /* init ncurses std screen */
    initscr();
    cbreak();
    noecho();
    // init color
    if (has_colors() == false) {
        wprintw(stdscr, "ERROR: The terminal don't support color output.");
        wrefresh(stdscr);
        wgetch(stdscr); // suspend
        werase(stdscr);
    } else {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLUE);
        init_pair(2, COLOR_RED, COLOR_BLACK);
    }

    // get maximum screen size, used to calculate the size of scene window
    int max_y;
    int max_x;
    getmaxyx(stdscr, max_y, max_x);
    WarmLog_General(&runtime_config, "main", "MAX screen X: %d, Y: %d\n", max_x, max_y);

    // logging
    WarmLog_General(&runtime_config, "main", "ncurses has been inited, starting Developer Terminal scene\n");

    // select the scene
    enum SceneSelectorEventIndex {
        kEventSceneDevelopTerminal = 0,
        kEventSceneProgramInfo = 1,
        kEventQuitProgram = 2,
    };
    wprintw(stdscr, "Choose the scene(For Develop):");
    struct WarmSelectorActionEvent scene_selector_event[3] = {
        {.string = "Develop Terminal",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 1,
         .position_x = 2},
        {.string = "Program info",
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .position_y = 2,
         .position_x = 2},
        {.string = "Quit Program",
         .attribute = A_DIM,
         .attribute_highlight = A_STANDOUT,
         .position_y = 3,
         .position_x = 2},
    };
    int selected_scene = DialogueSelector(&runtime_config, stdscr, scene_selector_event, 3);
    werase(stdscr);

    if (selected_scene == kEventSceneDevelopTerminal) { // scene - develop terminal
        attron(COLOR_PAIR(1));
        wprintw(stdscr, "Yeah,");
        attroff(COLOR_PAIR(1));
        wprintw(stdscr, " Welcome to WarmaShark, below is the develop terminal.\n");
        wprintw(stdscr, "======== ======== ======== ======== ========\n");
        wrefresh(stdscr);
        // create a window for develop terminal scene
        WINDOW *window = newwin((max_y - 2) * 0.4, max_x * 0.7, 2, 0);
        box(window, 0, 0);
        wrefresh(window);

        // creat a new windows without border
        delwin(window);
        window = newwin(((max_y - 2) * 0.4) - 2, (max_x * 0.7) - 2, 3, 1);
        // start test scene
        SceneStart_DevelopTerminal(&runtime_config, window);
    } else if (selected_scene == kEventSceneProgramInfo) { // scene - program info
        // show end info(full screen)
        SceneStart_ProgramInfo(&runtime_config, stdscr);
    } else if (selected_scene == kEventQuitProgram) { // quit program
        EngineRuntimeFreeUp(&runtime_config);
        endwin();
        exit(0);
    }

    // free up everything
    EngineRuntimeFreeUp(&runtime_config);
    endwin();

    return 0;
}
