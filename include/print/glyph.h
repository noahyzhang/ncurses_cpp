// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include <utility>
#include <vector>
#include "print/attribute.h"
#include "print/color_pair.h"

namespace ncurses_cpp {

class Glyph {
public:
    explicit Glyph(char c, ColorPair color = ColorPair(Color::white))
        : char_{c}, color_{color} {}

    explicit Glyph(char c, ColorPair color, std::vector<attribute> attribute)
        : char_{c}, color_{color}, attribute_{std::move(attribute)} {}

    void print(WINDOW* window) const {
        apply_color(window, color_);
        apply_attributes(window, attribute_);
        waddch(window, static_cast<chtype>(char_));
        wattrset(window, A_NORMAL);
    }

    const char data() const {
        return char_;
    }

    void add_attribute(const attribute attr) {
        attribute_.emplace_back(attr);
    }

    void set_attribute(const std::vector<attribute>& attrs) {
        attribute_ = attrs;
    }

    friend bool operator==(const Glyph& lhs, const Glyph& rhs) {
        return lhs.char_ == rhs.char_ && lhs.color_ == rhs.color_;
    }

    friend bool operator!=(const Glyph& lhs, const Glyph& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Glyph& lhs, const Glyph& rhs) {
        return std::tie(lhs.char_, lhs.color_) < std::tie(rhs.char_, rhs.color_);
    }

    friend bool operator>(const Glyph& lhs, const Glyph& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const Glyph& lhs, const Glyph& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const Glyph& lhs, const Glyph& rhs) {
        return !(lhs < rhs);
    }

private:
    char char_{'\0'};
    ColorPair color_;
    std::vector<attribute> attribute_;
};

}  // namespace ncurses_cpp
