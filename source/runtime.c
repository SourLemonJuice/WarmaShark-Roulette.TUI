#include "runtime.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>

/*
    Here needs to become the first function in the program. Don't forget this.

    return:
        0: no error
        non-zero: anyway, it just have error
 */
int EngineRuntimeInit(struct WarmRuntime *runtime)
{
    // set locale
    // NOTE: this step need before any IO operation, include the ncurses init!!!
    runtime->locale_string = getenv("LANG");
    if (runtime->locale_string == NULL)
        exit(1);
    setlocale(LC_ALL, runtime->locale_string); // setup program locale

    // setting log file
    runtime->log_path = "./Engine.log";
    runtime->log_handle = fopen(runtime->log_path, "w"); // open log file, and save the handle
    if (runtime->log_handle == NULL) {
        exit(1);
    } else {
        fprintf(runtime->log_handle, "==== Engine runtime has been init ====\n");
        fflush(runtime->log_handle);
    }

    // seeding for random number
    srand(time(NULL));

    return 0;
}

int EngineNcursesInit(struct WarmRuntime *runtime)
{
    // init ncurses std screen
    initscr();
    cbreak();
    noecho();

    // init ncurses color
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

    // maximum terminal size
    getmaxyx(stdscr, runtime->terminal_y, runtime->terminal_x);

    return 0;
}

/*
    Just will free up runtime data.
    Won't close ncurses lib, and also won't exit program.
 */
void EngineRuntimeUnload(struct WarmRuntime *runtime)
{
    fclose(runtime->log_handle);
}

/*
    Completely exit the program.
 */
void EngineRuntimeExit(struct WarmRuntime *runtime, int return_code)
{
    EngineRuntimeUnload(runtime);
    endwin();
    exit(return_code);
}
