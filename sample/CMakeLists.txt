set(CMAKE_CXX_STANDARD 17)

include_directories(
    ./include
)

add_executable(sample sample.cpp)

target_link_libraries(sample ncurses)
