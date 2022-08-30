cmake_minimum_required(VERSION 3.23)
project(asdf C)

set(CMAKE_C_STANDARD 99)

add_executable(asdf src/main.c src/tree.c src/tree.h src/asdf.c src/asdf.h src/dimensions.h)
target_link_libraries(asdf curses)
