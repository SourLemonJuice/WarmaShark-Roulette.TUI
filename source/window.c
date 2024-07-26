#include "window.h"

#include <iso646.h>

#include <ncurses.h>

#include "runtime.h"

/*
    Create a window use the percentage size and a set of align manage.

    note:
        - This function won't use subwindow.
        - The type of Center will ignore the offset.

    result:
        NULL: newwin() return value
 */
WINDOW *WindowPercentageCreate(struct WarmRuntime *runtime, WINDOW *parent_win, enum WindowHorizontalAlignType hor_type,
                               int hor_offset, enum WindowVerticalAlignType ver_type, int ver_offset,
                               float size_percent_y, float size_percent_x)
{
    int beg_y;
    int beg_x;
    getbegyx(parent_win, beg_y, beg_x);
    int par_size_y;
    int par_size_x;
    getmaxyx(parent_win, par_size_y, par_size_x);

    // size of the window to be returned
    if (size_percent_y > 1 or size_percent_x > 1)
        return NULL;
    int out_size_y = par_size_y * size_percent_y;
    int out_size_x = par_size_x * size_percent_x;

    int out_pos_y;
    switch (ver_type)
    {
    case kWindowTypeVerticalTop:
        out_pos_y = beg_y + ver_offset;
        break;
    case kWindowTypeVerticalBottom:
        out_pos_y = beg_y + par_size_y - out_size_y - ver_offset;
        break;
    case kWindowTypeVerticalCenter:
        out_pos_y = beg_y + (par_size_y - out_size_y) / 2;
        break;
    }

    int out_pos_x;
    switch (hor_type) {
    case kWindowTypeHorizontalLeft:
        out_pos_x = beg_x + hor_offset;
        break;
    case kWindowTypeHorizontalRight:
        out_pos_x = beg_x + par_size_x - out_size_x - hor_offset;
        break;
    case kWindowTypeHorizontalCenter:
        out_pos_x = beg_x + (par_size_x - out_size_x) / 2;
        break;
    }

    return newwin(out_size_y, out_size_x, out_pos_y, out_pos_x);
}

/*
    Create a border with box(), then delete the original window,
    and return a new pointer without the border size.
    The original window must be valid.

    return:
        same with the newwin() return value
 */
WINDOW *WindowEngravedBorder(struct WarmRuntime *runtime, WINDOW *win)
{
    box(win, 0, 0);
    wrefresh(win);

    int beg_y;
    int beg_x;
    getbegyx(win, beg_y, beg_x);
    int size_y;
    int size_x;
    getmaxyx(win, size_y, size_x);

    delwin(win);
    return newwin(size_y - 2, size_x - 2, beg_y + 1, beg_x + 1);
}
