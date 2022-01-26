#include "solve.h"

/* Should solve the sudoku */
void solve_sudoku(block *blocks) {
  int number_found;

  do {
    number_found = find_number(blocks);

  } while (number_found);

}

/* Should find the next number to put in the sudoku */
int find_number(block *blocks) {
  int temp_number_arr[NUM_OF_NUMS];
  int i = 0, j, k;
  int number_found = 0;
  int arr_pos = 0;

  while (!number_found) {
    j = 0;
    arr_pos = 0;

    while (!number_found){
      int check_number = blocks[i].numbers[j];

      if (!check_number) {
        /* looking at a new position */
        for (k = 0; k < NUM_OF_NUMS; k++){
          temp_number_arr[k] = -1;
        }
        arr_pos = 0;
        if (check_block(blocks, temp_number_arr, i, j, &arr_pos) ||
            check_horizontal(blocks, temp_number_arr, i, j, &arr_pos) ||
            check_vertical(blocks, temp_number_arr, i, j, &arr_pos)  ||
            exclusion_method(blocks, temp_number_arr, i, j, &arr_pos)){
          return 1;
        }

      }
      if (j < NUM_OF_NUMS-1){ /* have all numbers in the current block checked? */
        j++;  /* no */
      }
      else
        break; /* yes */
    }

    if (i < NUM_OF_BLOCKS-1){ /* have all the blocks been checked? */
      i++; /* no */
      continue;
    }
    else
      break; /* yes */
  }

  return 0;
}

/* checks the numbers that are already in the block */
int check_block(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int i, current_number;

  for (i = 0; i < NUM_OF_NUMS; i++){
    current_number = blocks[block_num].numbers[i];

    if (current_number > 0 && current_number < 10 && check_number(temp_number_arr, arr_pos, current_number)){
      temp_number_arr[*arr_pos] = current_number;
      ++(*arr_pos);
      if (*arr_pos == (NUM_OF_NUMS - 1)){
        insert_number(blocks, temp_number_arr, block_num, pos_num, arr_pos);
        return 1;
      }
      else
        continue;
    }
  }
  return 0;
}

/* checks the numbers that are horizontal with the field that's being checked */
int check_horizontal(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int pos_calc[3];
  int block_calc[3];
  int i, j, current_number;

  pos_calc[0] = pos_num;
  block_calc[0] = block_num;

  find_num_hor(pos_calc);
  find_num_hor(block_calc);

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      current_number = blocks[block_calc[i]].numbers[pos_calc[j]];

      if (current_number > 0 && current_number < 10 && check_number(temp_number_arr, arr_pos, current_number)){
        temp_number_arr[*arr_pos] = current_number;
        ++(*arr_pos);

        if (*arr_pos == (NUM_OF_NUMS - 1)){
          insert_number(blocks, temp_number_arr, block_num, pos_num, arr_pos);
          return 1;
        }
        else
          continue;
      }
    }
  }
  return 0;
}

/* checks the numbers that are vertical with the field that's being checked */
int check_vertical(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int pos_calc[3];
  int block_calc[3];
  int i, j;
  int current_number;

  pos_calc[0] = pos_num;
  block_calc[0] = block_num;

  find_num_ver(pos_calc);
  find_num_ver(block_calc);

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      current_number = blocks[block_calc[i]].numbers[pos_calc[j]];

      if (current_number > 0 && current_number < 10 && check_number(temp_number_arr, arr_pos, current_number)){
        temp_number_arr[*arr_pos] = current_number;
        ++(*arr_pos);

        if (*arr_pos == (NUM_OF_NUMS - 1)){
          insert_number(blocks, temp_number_arr, block_num, pos_num, arr_pos);
          return 1;
        }
        else
          continue;
      }
    }
  }

  return 0;
}

/* checks if the number is in the temporary array */
int check_number(int *temp_number_arr, int *arr_pos, int number) {
  int i;

  for (i = 0; i < *arr_pos; i++){
    if (number == temp_number_arr[i])
      return 0;
  }
  return 1;
}

/* inserts the number in the sudoku */
void insert_number(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int num_being_checked = 1;
  int num_placed = 0;
  int i;

  while (!num_placed){
    for (i = 0; i < *arr_pos; i++){

      if (num_being_checked == temp_number_arr[i]){ /* If the number is already taken */
        break;
      }
      else if (i == *arr_pos-1){ /* If the end of the array has been reached */
        blocks[block_num].numbers[pos_num] = num_being_checked;

        num_placed = 1;
        break;
      }

    }

    if (num_being_checked <= NUM_OF_NUMS)
      num_being_checked++;
    else
      break;
  }
}



