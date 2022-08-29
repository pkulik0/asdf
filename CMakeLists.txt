cmake_minimum_required(VERSION 3.23)
project(asdf C)

set(CMAKE_C_STANDARD 99)

add_executable(asdf src/main.c src/tree.h src/window.h src/dimensions.h src/tree.c)
target_link_libraries(asdf curses)
