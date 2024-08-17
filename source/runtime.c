#include "runtime.h"

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>
#if _WIN32
    #include <windows.h>
#endif

/*
    Initialize some structure member
 */
int EngineRuntimeInit(struct WarmRuntime *runtime)
{
    // default log path
    runtime->log_path = "./Engine.log";

    // disable logging by default
    runtime->logging = false;

    // seeding for random number
    srand(time(NULL));

    return 0;
}

/*
    Set locale
    NOTE: this step need before any IO operation, include the ncurses init!!!
 */
void EngineSetLocale(struct WarmRuntime *runtime)
{
    runtime->locale_string = setlocale(LC_ALL, "C.UTF-8");

#if _WIN32
    // maybe it could be some use? Well... it won't
    SetConsoleOutputCP(65001);
#endif

    return;
}

/*
    Initialize program log system
 */
int EngineLogSystemInit(struct WarmRuntime *runtime)
{
    if (runtime->logging == false)
        return 0;

    // open log file
    runtime->log_handle = fopen(runtime->log_path, "w"); // open log file, and save the handle
    if (runtime->log_handle == NULL) {
        exit(kWarmErrorStreamOperation);
    } else {
        fprintf(runtime->log_handle, "==== [Engine logging system has been init] ====\n");
        fflush(runtime->log_handle);
    }

    return 0;
}

/*
    Initialize ncurses library
 */
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
        init_pair(kColorTest, COLOR_YELLOW, COLOR_BLUE);
        init_pair(kColorDangerRed, COLOR_RED, COLOR_BLACK);
        init_pair(kColorFlowerYellow, COLOR_YELLOW, COLOR_BLACK);
        init_pair(kColorAdminMessage, COLOR_MAGENTA, COLOR_BLACK);
    }

    // maximum terminal size
    getmaxyx(stdscr, runtime->terminal_y, runtime->terminal_x);

    return 0;
}

/*
    Just will free up runtime data.
    Won't close ncurses lib, and also won't exit program.
 */
void EngineLogSystemUnload(struct WarmRuntime *runtime)
{
    // if log has been disabled, don't fclose a non-existent "FILE*"
    if (runtime->logging == false)
        return;

    fclose(runtime->log_handle);
}

/*
    Completely exit the program.
 */
void EngineFullExit(struct WarmRuntime *runtime, int return_code)
{
    EngineLogSystemUnload(runtime);
    endwin();
    exit(return_code);
}
