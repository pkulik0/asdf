cmake_minimum_required(VERSION 3.23)
project(asdf C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra")

include_directories(src)

include_directories(/Library/Frameworks/Python.framework/Versions/3.10/include/python3.10)
link_directories(/Library/Frameworks/Python.framework/Versions/3.10/lib)

link_libraries(curses python3.10)

add_executable(asdf src/main.c src/window/tree.c src/window/tree.h src/asdf.c src/asdf.h src/window/dimensions.h src/file.h src/file.c src/scripts.h src/scripts.c src/modules/editor.h src/modules/editor.c)
add_executable(test tests/suite.h tests/tests.c src/window/tree.c src/window/tree.h src/asdf.c src/asdf.h src/window/dimensions.h src/file.h src/file.c src/scripts.h src/scripts.c src/modules/editor.h src/modules/editor.c)

