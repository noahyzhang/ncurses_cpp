// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <utility>
#include "print/glyph.h"

namespace ncurses_cpp {

class GlyphString : public std::vector<Glyph> {
public:
    GlyphString() = default;
    ~GlyphString() = default;
    GlyphString(const GlyphString&) = default;
    GlyphString& operator=(const GlyphString&) = default;
    GlyphString(GlyphString&&) = default;
    GlyphString& operator=(GlyphString&&) = default;
    explicit GlyphString(std::string_view str, ColorPair color = ColorPair(Color::white)) {
        for (const auto& c : str) {
            emplace_back(c, color);
        }
    }

    void print(WINDOW* win) const {
        for (const auto& g : *this) {
            g.print(win);
        }
    }
};

inline GlyphString parse_arg(std::string_view, GlyphString&) { return {}; }

template <typename T, typename... Args>
inline GlyphString parse_arg(std::string_view to_parse, GlyphString& parsed, const T& arg, Args&&... args) {
    auto colors = ColorPair(Color::white);
    auto attributes = std::vector<attribute>();
    size_t pos = 0;
    for (auto ch = std::begin(to_parse); *ch != '}'; ++ch, ++pos) {
        if (char_to_color.count(*ch)) {
            colors = ColorPair(to_color(*ch));
        }
        if (char_to_attribute.count(*ch)) {
            attributes.emplace_back(to_attribute(*ch));
        }
    }
    std::stringstream oss;
    oss << arg;
    auto parsed_arg = GlyphString(oss.str(), colors);
    for (auto& g : parsed_arg) {
        g.set_attribute(attributes);
    }
    std::move(parsed_arg.begin(), parsed_arg.end(), std::back_inserter(parsed));
    to_parse.remove_prefix(std::min(pos+1, to_parse.size()));
    return parse(to_parse, parsed, std::forward<Args>(args)...);
}

template <typename... Args>
inline GlyphString parse(std::string_view to_parse, GlyphString& parsed, Args&&... args) {
    size_t pos = 0;
    for (auto ch : to_parse) {
        if (ch != '{') {
            parsed.emplace_back(ch);
        } else {
            to_parse.remove_prefix(pos);
            return parse_arg(to_parse, parsed, std::forward<Args>(args)...);
        }
        ++pos;
    }
    return parsed;
}

}  // namespace ncurses_cpp
