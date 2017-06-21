cmake_minimum_required(VERSION 3.7)
project(base)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c src/check.h src/check.c)
add_executable(base ${SOURCE_FILES})