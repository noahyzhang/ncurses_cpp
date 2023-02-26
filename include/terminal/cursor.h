// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include "curses.h"

namespace ncurses_cpp {

class CursesError : public std::runtime_error {
public:
    explicit CursesError(const std::string& arg) : runtime_error(arg) {}
};

inline void error_check(int return_val, const std::string& what_msg) {
    if (return_val == ERR) {
        throw CursesError(what_msg);
    }
}

inline int set_echo(bool mode) {
    if (mode) {
        return echo();
    }
    return noecho();
}

struct Cursor {
public:
    enum class visibility {
        invisible = 0,
        normal = 1,
        high = 2
    };

    static void set_visibility(visibility v) {
        error_check(curs_set(static_cast<int>(v)), "Your terminal not support specified visibility mode");
    }
};

}  // namespace ncurses_cpp
