#pragma once

#include <ncurses.h>

#include "runtime.h"

// note: center don't have offset

enum WindowHorizontalAlignType {
    kWindowTypeHorizontalLeft,
    kWindowTypeHorizontalRight,
    kWindowTypeHorizontalCenter,
};

enum WindowVerticalAlignType {
    kWindowTypeVerticalTop,
    kWindowTypeVerticalBottom,
    kWindowTypeVerticalCenter,
};

WINDOW *WindowPercentageCreate(struct WarmRuntime *runtime, WINDOW *parent_win, enum WindowHorizontalAlignType hor_type,
                               int hor_offset, enum WindowVerticalAlignType ver_type, int ver_offset,
                               float size_percent_y, float size_percent_x);
WINDOW *WindowEngravedBorder(struct WarmRuntime *runtime, WINDOW *win);
