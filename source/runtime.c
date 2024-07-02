#include "runtime.h"

#include <locale.h>
#include <stdio.h>

#include <ncurses.h>

int EngineReloadLocale(const struct WarmRuntimeConfig *config)
{
    setlocale(LC_ALL, config->locale_string);
    return 0;
}

/*
    Here needs to become the first function in the program. Don't forget this.

    return:
        0: no error
        non-zero: anyway, it just have error
 */
int EngineRuntimeInit(struct WarmRuntimeConfig *config)
{
    // set locale
    // NOTE: this step need before any IO operation, include the ncurses init!!!
    config->locale_string = "en_US.UTF-8";
    EngineReloadLocale(config); // setup program locale

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
    config->log_path = "./Engine.log";
    config->log_handle = fopen(config->log_path, "w"); // open log file, and save the handle
    if (config->log_handle == NULL) {
        return 1;
    } else {
        fprintf(config->log_handle, "==== Engine runtime has been init ====\n");
        fflush(config->log_handle);
    }

    // maximum terminal size
    getmaxyx(stdscr, config->terminal_y, config->terminal_x);

    return 0;
}

int EngineRuntimeFreeUp(struct WarmRuntimeConfig *config)
{
    fclose(config->log_handle);
    return 0;
}
