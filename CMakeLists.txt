cmake_minimum_required(VERSION 3.1)
project(multicopia)

set(CMAKE_C_FLAGS "-std=c99")

set(SOURCE_FILES main.c)
add_executable(multicopia ${SOURCE_FILES})