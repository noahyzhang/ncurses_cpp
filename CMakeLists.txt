cmake_minimum_required(VERSION 3.16.3)
project(ncurses_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ./include
)

add_subdirectory(sample)
