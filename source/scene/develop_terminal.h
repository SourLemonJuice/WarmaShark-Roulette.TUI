#ifndef WARM_SCENE_DEVELOP_TERMINAL_H_
#define WARM_SCENE_DEVELOP_TERMINAL_H_

#include <ncurses.h>

#include "runtime.h"

// TODO dialogue event shouldn't be implemented by scene self
struct DialogueEvent {
    // what message will be printw()
    char *text;
    // is this sentence finished? if `flase` will not wait a key and clear the window
    bool finished;
    // the ncurses color paird id
    int color_id;
    // TODO speak rate
};

int SceneStart_DevelopTerminal(struct WarmRuntimeConfig *engine_runtime, WINDOW *win_handle);

#endif
