cmake_minimum_required(VERSION 3.7)
project(base)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c src/check.h src/check.c src/copy.c src/copy.h src/fcopy.c src/fcopy.h)
add_executable(simple-run ${SOURCE_FILES})