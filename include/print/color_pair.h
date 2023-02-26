// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include "print/color.h"

namespace ncurses_cpp {

struct ColorPair {
    using type = std::pair<Color, Color>;
    explicit ColorPair(Color fg = Color::white, Color bg = Color::none) {
        auto pair = std::pair<Color, Color>(fg, bg);
        auto pos = std::find(std::begin(initialized_pairs), std::end(initialized_pairs), pair);
        if (pos != std::end(initialized_pairs)) {
            pair_number = static_cast<uint64_t>(std::distance(std::begin(initialized_pairs), pos) + 1);
        } else {
            init_pair(initialized_pairs.size() + 1, static_cast<uint8_t>(fg), static_cast<uint8_t>(bg));
            initialized_pairs.emplace_back(pair);
            pair_number = initialized_pairs.size();
        }
    }

    explicit ColorPair(uint64_t pair_num) : pair_number(pair_num) {
        if (pair_num > initialized_pairs.size()) {
            throw std::invalid_argument("This color pair doesn't exist: " + std::to_string(pair_num));
        }
    }

    friend bool operator==(const ColorPair& lhs, const ColorPair& rhs) {
        return lhs.pair_number == rhs.pair_number;
    }

    friend bool operator!=(const ColorPair& lhs, const ColorPair& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const ColorPair& lhs, const ColorPair& rhs) {
        return lhs.pair_number < rhs.pair_number;
    }

    friend bool operator>(const ColorPair& lhs, const ColorPair& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const ColorPair& lhs, const ColorPair& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const ColorPair& lhs, const ColorPair& rhs) {
        return !(lhs < rhs);
    }

    uint64_t pair_number{0};
    static std::vector<type> initialized_pairs;
};

inline std::vector<ColorPair::type> ColorPair::initialized_pairs{};

inline void apply_color(WINDOW* window, ColorPair c) {
    wattron(window, COLOR_PAIR(c.pair_number));
}

}  // namespace ncurses_cpp
