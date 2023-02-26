#include "ncurses_cpp.h"


class CustomType {
public:
    friend std::ostream& operator<<(std::ostream& os, const CustomType& type) {
        return os << "str: " << type.str_ << " pi: " << type.pi_;
    }

private:
    const std::string str_{"user defined"};
    const double pi_{3.14};
};

int main() {
    ncurses_cpp::Terminal terminal;
    auto& main_win = terminal.get_main_win();

    mvprintw(0, 0, "hello world");

    main_win << ncurses_cpp::format(2, 0)("ncurses_cpp sample");

    // main_win << ncurses_cpp::format(2, 0)("Enter with color characters {rR} {gB}!", "hello", "world");

    // main_win << ncurses_cpp::format(3, 0)("Supports {R} types!", CustomType{});

    // auto child_win{ncurses_cpp::Window{{10, 5, 5, 30}, main_win}};
    // child_win << ncurses_cpp::format(2, 2)("Hello from child_win");

    // child_win.get_char();

    main_win.get_char();
    return 0;
}
