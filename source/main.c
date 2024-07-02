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
    // init program
    struct WarmRuntimeConfig runtime;
    EngineRuntimeInit(&runtime);

    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // if have any arguments, then break program
    if (argc >= 2) {
        WarmLog_Warning(&runtime, "main", "there is a CLI argument input here, we don't use it\n");
    }
    // record some information for tracking
    WarmLog_General(&runtime, "main", "Program locale should have been set to %s\n", runtime.locale_string);
    WarmLog_General(&runtime, "main", "MAX screen X: %d, Y: %d\n", runtime.terminal_x, runtime.terminal_y);
    WarmLog_General(&runtime, "main", "program runtime has been init, starting scene selector\n");

    // select the scene
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
    int selected_scene = DialogueSelector(&runtime, stdscr, scene_selector_event, 3);
    werase(stdscr);

    if (selected_scene == 0) { // scene - develop terminal
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
    } else if (selected_scene == 1) { // scene - program info
        // show end info(full screen)
        SceneStart_ProgramInfo(&runtime, stdscr);
    } else if (selected_scene == 2) { // quit program
        EngineRuntimeFreeUp(&runtime);
        endwin();
        exit(0);
    }

    // free up everything
    EngineRuntimeFreeUp(&runtime);
    endwin();

    return 0;
}
