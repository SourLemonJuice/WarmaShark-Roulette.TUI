#ifndef WARM_SCENE_DEVELOP_TERMINAL_H_
#define WARM_SCENE_DEVELOP_TERMINAL_H_

#include <ncurses.h>

struct dialogue_event
{
    char *text;
};

struct scene_runtime
{
    int dialogue1_size;
};

int sceneStart_DevelopTerminal(WINDOW *win_handle);

#endif
