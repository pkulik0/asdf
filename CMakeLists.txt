cmake_minimum_required(VERSION 3.23)
project(asdf C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra")

add_executable(asdf src/main.c src/tree.c src/tree.h src/asdf.c src/asdf.h src/dimensions.h src/files.h src/files.c src/scripts.h src/scripts.c)
add_executable(test tests/suite.c tests/suite.h tests/tests.c src/tree.c src/tree.h src/asdf.c src/asdf.h src/dimensions.h src/files.h src/files.c src/scripts.h src/scripts.c)

add_subdirectory(Lua)

set(LIBRARIES curses lua_static)
target_link_libraries(asdf ${LIBRARIES})
target_link_libraries(test ${LIBRARIES})