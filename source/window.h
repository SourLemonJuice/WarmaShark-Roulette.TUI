#pragma once

#include <ncurses.h>

#include "runtime.h"

enum WindowHorizontalAlignType {
    kWindowTypeHorizontalLeft,
    kWindowTypeHorizontalRight,
    kWindowTypeHorizontalCenter, // center don't have offset
};

enum WindowVerticalAlignType {
    kWindowTypeVerticalTop,
    kWindowTypeVerticalBottom,
};

WINDOW *WindowPercentageCreate(struct WarmRuntime *runtime, WINDOW *parent_win, enum WindowHorizontalAlignType hor_type,
                               int hor_offset, enum WindowVerticalAlignType ver_type, int ver_offset,
                               float size_percent_y, float size_percent_x);
WINDOW *WindowEngravedBorder(struct WarmRuntime *runtime, WINDOW *win);
