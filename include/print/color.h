// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include <unordered_map>
#include "curses.h"

namespace ncurses_cpp {

enum class Color : int8_t {
    none = -1,
    red = COLOR_RED,
    green = COLOR_GREEN,
    yellow = COLOR_YELLOW,
    blue = COLOR_BLUE,
    magenta = COLOR_MAGENTA,
    cyan = COLOR_CYAN,
    white = COLOR_WHITE,
    black = COLOR_BLACK,
};

static const std::unordered_map<char, Color> char_to_color {
    {'r', Color::red}, {'g', Color::green}, {'y', Color::yellow},
    {'b', Color::blue}, {'m', Color::magenta}, {'c', Color::cyan},
    {'w', Color::white}
};

inline Color to_color(char c) {
    return char_to_color.at(c);
}

}  // namespace ncurses_cpp
