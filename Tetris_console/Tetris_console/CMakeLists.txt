cmake_minimum_required(VERSION 3.21)
project(Tetris_console)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

add_executable(Tetris_console Tetris_console.cpp Tetris_console.h)
add_executable(t31 test.cpp Tetris_console.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

enable_testing()