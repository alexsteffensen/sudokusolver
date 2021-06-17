#ifndef SUDOKUSOLVER_SOLVE_H
#define SUDOKUSOLVER_SOLVE_H
#include "sudoku.h"
#include "exclusion.h"
#include "debug.h"
#include <stdio.h>

void solve_sudoku(block *blocks);
int find_number(block *blocks);
int check_horizontal(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
int check_vertical(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
int check_block(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
int check_number(int *temp_number_arr, int *arr_pos, int number);
void insert_number(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);

#endif
