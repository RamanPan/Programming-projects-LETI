cmake_minimum_required(VERSION 3.23)
project(Tic_tac_toe C)

set(CMAKE_C_STANDARD 11)

add_executable(Tic_tac_toe main.c functionality.c functionality.h)
