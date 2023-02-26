// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

namespace ncurses_cpp {

class WidgetInterface {
public:
    WidgetInterface() = default;
    WidgetInterface(const WidgetInterface&) = delete;
    WidgetInterface& operator=(const WidgetInterface&) = delete;
    WidgetInterface(WidgetInterface&&) = delete;
    WidgetInterface& operator=(WidgetInterface&&) = delete;

public:
    virtual ~WidgetInterface() = default;
    virtual void draw() const = 0;
    virtual void refresh() const = 0;
};

} // ncurses_cpp
