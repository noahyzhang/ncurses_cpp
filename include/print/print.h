// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include <utility>
#include <string>
#include <string_view>
#include "print/glyph_string.h"
#include "widget/window.h"

namespace ncurses_cpp {

struct Printer {
    template <typename... Args>
    Printer operator()(std::string_view str, Args&&... args) {
        parse(str, format_str, (std::forward<Args>(args))...);
        return *this;
    }
    const std::pair<int, int> coords;
    GlyphString format_str;
};

inline Printer format(const int y, const int x) {
    return {std::make_pair(y, x)};
}

template <typename... Args>
inline Printer format(std::string_view str, Args&&... args) {
    GlyphString format_str;
    parse(str, format_str, (std::forward<Args>(args))...);
    return Printer{std::make_pair(0, 0), format_str};
}

inline const WindowInterface& operator<<(const WindowInterface& w, const Printer& formatted) {
    const auto x = formatted.coords.second
        ? formatted.coords.second
        : (w.get_max_yx().second - formatted.format_str.size()) / 2;
    const auto y = formatted.coords.first
        ? formatted.coords.first
        : w.get_curr_yx().first;
    w.move_cursor(y, x);
    formatted.format_str.print(w.get());
    return w;
}

}  // namespace ncurses_cpp
