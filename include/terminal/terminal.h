// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include "print/print.h"
#include "widget/widget.h"
#include "terminal/cursor.h"
#include "curses.h"

namespace ncurses_cpp {

class Terminal {
public:
    Terminal() {
        initscr();
        keypad(stdscr, TRUE);
        set_echo(false);
        Cursor::set_visibility(Cursor::visibility::invisible);
        if (!has_colors()) {
            main_win << format("your terminal does not support color!");
        } else {
            start_color();
            use_default_colors();
            init_color_pairs();
        }
    }
    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;
    Terminal(Terminal&&) = delete;
    Terminal& operator=(Terminal&&) = delete;
    ~Terminal() {
        attrset(A_NORMAL);
        endwin();
        fflush(stdout);
    }

    StdscrWrapper& get_main_win() {
        return main_win;
    }

private:
    void init_color_pairs() {
        ColorPair(Color::red, Color::none);
        ColorPair(Color::green, Color::none);
        ColorPair(Color::yellow, Color::none);
        ColorPair(Color::blue, Color::none);
        ColorPair(Color::magenta, Color::none);
        ColorPair(Color::cyan, Color::none);
        ColorPair(Color::white, Color::none);
    }

private:
    StdscrWrapper main_win;
};

}  // namespace ncurses_cpp
