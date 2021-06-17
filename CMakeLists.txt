cmake_minimum_required(VERSION 3.13)
project(sudokusolver)

add_executable(Cmake main.c debug.c debug.h sudoku.h exclusion.c exclusion.h solve.h solve.c interpreter.c interpreter.h)

