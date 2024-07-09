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
    runtime->locale_string = "en_US.UTF-8";
    setlocale(LC_ALL, runtime->locale_string); // setup program locale

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
    }

    // setting log file
    runtime->log_path = "./Engine.log";
    runtime->log_handle = fopen(runtime->log_path, "w"); // open log file, and save the handle
    if (runtime->log_handle == NULL) {
        return 1;
    } else {
        fprintf(runtime->log_handle, "==== Engine runtime has been init ====\n");
        fflush(runtime->log_handle);
    }

    // maximum terminal size
    getmaxyx(stdscr, runtime->terminal_y, runtime->terminal_x);

    // seeding for random number
    srand(time(NULL));

    return 0;
}

void EngineRuntimeUnload(struct WarmRuntime *runtime, int return_code)
{
    fclose(runtime->log_handle);
    endwin();
    exit(return_code);
}
