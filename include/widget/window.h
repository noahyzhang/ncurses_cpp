// Copyright 2023 Tencent LLC
// Author: noahyzhang

#pragma once

#include <utility>
#include <vector>
#include <memory>
#include "curses.h"
#include "widget/widget.h"

namespace ncurses_cpp {

class WindowInterface : public WidgetInterface {
public:
    virtual void get_char() const = 0;
    virtual std::pair<int, int> get_curr_yx() const = 0;
    virtual std::pair<int, int> get_max_yx() const = 0;
    virtual WINDOW* get() const = 0;
    virtual void move_cursor(int y, int x) const = 0;
};

class StdscrWrapper : public WindowInterface {
public:
    void draw() const override {
        wrefresh(stdscr);
    }
    void refresh() const override {
        wrefresh(stdscr);
    }
    void get_char() const override {
        wgetch(stdscr);
    }
    std::pair<int, int> get_curr_yx() const override {
        int y = 0, x = 0;
        getyx(get(), y, x);
        return {y, x};
    }
    std::pair<int, int> get_max_yx() const override {
        int y = 0, x = 0;
        getmaxyx(get(), y, x);
        return {y, x};
    }
    WINDOW* get() const override {
        return stdscr;
    }
    void move_cursor(int y, int x) const override {
        wmove(get(), y, x);
    }
};

class Window : public WindowInterface {
public:
    struct dimensions {
        int y{0};
        int x{0};
        int height{0};
        int width{0};
    };
    Window(dimensions dims, WidgetInterface& hook)
        : dimensions_(dims), hook_(hook) {
        raw_window_ = std::unique_ptr<WINDOW, WindowDeleter>(
            newwin(dimensions_.height, dimensions_.width, dimensions_.y, dimensions_.x));
        hook_.refresh();
        refresh();
        box(raw_window_.get(), 0, 0);
    }
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;
    ~Window() override = default;

public:
    void draw() const override {
        wclear(raw_window_.get());
        for (const auto& w : children_) {
            w->draw();
        }
        hook_.refresh();
        box(raw_window_.get(), 0, 0);
        refresh();
    }

    void add_widget(std::unique_ptr<WidgetInterface> w) {
        children_.emplace_back(std::move(w));
    }

    void refresh() const override {
        hook_.refresh();
        wrefresh(raw_window_.get());
        for (const auto& w : children_) {
            w->refresh();
        }
    }

    void get_char() const override {
        hook_.refresh();
        refresh();
        wgetch(raw_window_.get());
    }

    WINDOW* get() const override {
        return raw_window_.get();
    }

    std::pair<int, int> get_curr_yx() const override {
        int y = 0, x = 0;
        getyx(get(), y, x);
        return {y, x};
    }

    std::pair<int, int> get_max_yx() const override {
        int y = 0, x = 0;
        getmaxyx(get(), y, x);
        return {y, x};
    }

    void move_cursor(int y, int x) const override {
        wmove(get(), y, x);
    }

private:
    dimensions dimensions_;
    WidgetInterface& hook_;
    std::vector<std::unique_ptr<WidgetInterface>> children_;

    struct WindowDeleter {
        void operator()(WINDOW* window) const {
            wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            wclear(window);
            wrefresh(window);
            delwin(window);
        }
    };
    std::unique_ptr<WINDOW, WindowDeleter> raw_window_;
};

}  // namespace ncurses_cpp
