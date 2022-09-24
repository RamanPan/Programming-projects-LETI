cmake_minimum_required(VERSION 3.23)
project(SnakeGame C)

set(CMAKE_C_STANDARD 11)

add_executable(SnakeGame main.c functionality.h functionality.c)
