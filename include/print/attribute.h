// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include <unordered_map>
#include <vector>
#include "curses.h"

namespace ncurses_cpp {

enum class attribute {
    normal = A_NORMAL,
    standout = A_STANDOUT,
    underline = A_UNDERLINE,
    reverse = A_REVERSE,
    blink = A_BLINK,
    dim = A_DIM,
    bold = A_BOLD,
    protect = A_PROTECT,
    invisible = A_INVIS
};

static const std::unordered_map<char, attribute> char_to_attribute {
    {'N', attribute::normal}, {'S', attribute::standout},
    {'U', attribute::underline}, {'R', attribute::reverse},
    {'X', attribute::blink}, {'D', attribute::dim},
    {'B', attribute::bold}, {'P', attribute::protect},
    {'I', attribute::invisible}
};

inline attribute to_attribute(char c) {
    return char_to_attribute.at(c);
}

template <typename... Attrs>
inline void apply_attributes(WINDOW* window, Attrs... attrs) {
    wattron(window, (attrs | ...));
}

inline void apply_attributes(WINDOW* window, const std::vector<attribute>& attrs) {
    for (const auto& attr : attrs) {
        wattron(window, static_cast<chtype>(attr));
    }
}

}  // namespace ncurses_cpp
