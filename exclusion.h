#ifndef SUDOKUSOLVER_EXCLUSION_H
#define SUDOKUSOLVER_EXCLUSION_H
#include "sudoku.h"
#include <stdio.h>

int exclusion_method(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
void find_numbers(int *temp_number_arr, int *arr_pos, int *search_nums);
void find_remaining_pos(block *blocks, int block_num, int pos_num, int* remain_pos);
int check_positions(block *blocks, int block_num, int *remain_pos, int arr_len, int num);
int check_horizontal_exclusion(block *blocks, int block_num, int remain_pos, int arr_len, int num);
int check_vertical_exclusion(block *blocks, int block_num, int remain_pos, int arr_len, int num);
int check_pos_exclusion(block *blocks, int block_num, int pos_num, int num);
int find_pos_num(block *blocks, int block_num, int pos_num);
void find_num_hor(int *pos_calc);
void find_num_ver(int *block_calc);

#endif
