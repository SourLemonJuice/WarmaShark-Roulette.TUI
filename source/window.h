#pragma once

#include <ncurses.h>

#include "runtime.h"

enum WindowStyleType {
    kWindowTypeBlank,
    kWindowTypeBorder,
};

// note: center don't have offset
// Why I used "Type" but not "Attr" befor??
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

struct WindowAttribute {
    enum WindowStyleType style;
    enum WindowHorizontalAlignType hor_type;
    int hor_offset;
    enum WindowVerticalAlignType ver_type;
    int ver_offset;
};

struct WindowRecordNode {
    WINDOW *win;
    struct WindowAttribute attr;
    struct WindowRecordNode *previous;
    struct WindowRecordNode **next;
    int next_size;
};

WINDOW *WindowPercentageCreate(struct WarmRuntime *runtime, WINDOW *parent_win, enum WindowHorizontalAlignType hor_type,
                               int hor_offset, enum WindowVerticalAlignType ver_type, int ver_offset,
                               float size_percent_y, float size_percent_x);
WINDOW *WindowEngravedBorder(struct WarmRuntime *runtime, WINDOW *win);
