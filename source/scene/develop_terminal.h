#ifndef WARM_SCENE_DEVELOP_TERMINAL_H_
#define WARM_SCENE_DEVELOP_TERMINAL_H_

#include <ncurses.h>

#include "engine/engine_config.h"

// TODO dialogue event shouldn't be implemented by scene self
struct DialogueEvent {
    bool await;
    char *text;
    int keep_ms;
    int delay;
    int color_id;
};

struct SceneCache_DevelopTerminal {
    int dialogue1_size;
};

int SceneStart_DevelopTerminal(struct WarmRuntimeConfig *engine_runtime, WINDOW *win_handle, int start_y, int start_x);

#endif
