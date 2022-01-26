#include "exclusion.h"

/* Uses the exclusion method on the position given. */
int exclusion_method(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int arr_len = NUM_OF_NUMS - *arr_pos;
  int search_nums[arr_len];
  int remain_pos_len = find_pos_num(blocks, block_num, pos_num);
  int remain_pos[remain_pos_len];
  int i;

  find_numbers(temp_number_arr, arr_pos, search_nums);
  find_remaining_pos(blocks, block_num, pos_num, remain_pos);

  /*looping over the numbers that should be checked for*/
  for (i = 0; i < arr_len; i++) {
    if (check_positions(blocks, block_num, remain_pos, remain_pos_len, search_nums[i])){
      blocks[block_num].numbers[pos_num] = search_nums[i];
      return 1;
    }
  }
  return 0;
}

/* finds how many numbers that needs to be checked for in the exclusion method */
int find_pos_num(block *blocks, int block_num, int pos_num) {
  int i;
  int arr_len = 0;
  int current_pos_value;

  for (i = 0; i < NUM_OF_NUMS; i++){
    current_pos_value = blocks[block_num].numbers[i];
    if (i == pos_num)
      continue;
    else if (current_pos_value == 0)
      arr_len++;
  }
  return arr_len;
}

/* finds the numbers that needs to be checked for in the exclusion method */
void find_numbers(int *temp_number_arr, int *arr_pos, int *search_nums){
  int numbers_found = 0;
  int check_num = 1;
  int i, j = 0;

  while (!numbers_found) {
    for (i = 0; i < *arr_pos; i++) {
      if (temp_number_arr[i] == check_num)
        break;

      if (i == (*arr_pos - 1)){
        search_nums[j] = check_num;
        j++;
        break;
      }
    }
    if (check_num < NUM_OF_NUMS)
      check_num++;
    else
      numbers_found = 1;
  }
}

/* This function finds the positions which should be checked */
void find_remaining_pos(block *blocks, int block_num, int pos_num, int* remain_pos) {
  int pos, j = 0, current_number;

  for (pos = 0; pos < NUM_OF_NUMS; pos++){
    if (pos == pos_num)
      continue;

    current_number = blocks[block_num].numbers[pos];

    if (current_number == 0){
      remain_pos[j] = pos;
      j++;
    }
  }
}


/* Skal holde styr på om den position der tjekkes kan få tallet sat ind eller ej */
int check_positions(block *blocks, int block_num, int *remain_pos, int arr_len, int num) {
  int i;

  for (i = 0; i < arr_len; i++){
    if (check_horizontal_exclusion(blocks, block_num, remain_pos[i], arr_len, num) ||
        check_vertical_exclusion(blocks, block_num, remain_pos[i], arr_len, num)) {
      if (i == arr_len - 1)
        return 1;
    }
    else
      return 0;
  }
  return 0;
}

/* checks the horizontal positions of a field for a specific num */
int check_horizontal_exclusion(block *blocks, int block_num, int checking_pos, int arr_len, int num) {
  int pos_calc[3];
  int block_calc[3];
  int i, j;

  pos_calc[0] = checking_pos;
  block_calc[0] = block_num;

  find_num_hor(pos_calc);
  find_num_hor(block_calc);

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      if (check_pos_exclusion(blocks, block_calc[i], pos_calc[j], num))
        return 1;
    }
  }
  return 0;
}

/* checks the vertical positions of a field for a specific num */
int check_vertical_exclusion(block *blocks, int block_num, int checking_pos, int arr_len, int num) {
  int pos_calc[3];
  int block_calc[3];
  int i, j;

  pos_calc[0] = checking_pos;
  block_calc[0] = block_num;

  find_num_ver(pos_calc);
  find_num_ver(block_calc);

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      if (check_pos_exclusion(blocks, block_calc[i], pos_calc[j], num))
        return 1;
    }
  }
  return 0;
}

/* checks if a position has that number */
int check_pos_exclusion(block *blocks, int block_num, int pos_num, int num) {
  int current_number = blocks[block_num].numbers[pos_num];

  if (current_number == num)
    return 1;
  return 0;
}

/* Finds the horizontal block and position numbers that are needed to check the positions in exclusion method */
void find_num_hor(int *hor_nums) {
  switch (hor_nums[0] % 3) {
    case 0:
      hor_nums[1] = hor_nums[0] + 1;
      hor_nums[2] = hor_nums[0] + 2;
      break;

    case 1:
      hor_nums[1] = hor_nums[0] - 1;
      hor_nums[2] = hor_nums[0] + 1;
      break;

    case 2:
      hor_nums[1] = hor_nums[0] - 2;
      hor_nums[2] = hor_nums[0] - 1;
      break;

    default:  break;
  }
}

/* Finds the vertical block and position numbers that are needed to check the positions in exclusion method */
void find_num_ver(int *ver_nums) {
  switch (ver_nums[0] / 3) {
    case 0:
      ver_nums[1] = ver_nums[0] + (1*3);
      ver_nums[2] = ver_nums[0] + (2*3);
      break;

    case 1:
      ver_nums[1] = ver_nums[0] - 3;
      ver_nums[2] = ver_nums[0] + 3;
      break;

    case 2:
      ver_nums[1] = ver_nums[0] - (2*3);
      ver_nums[2] = ver_nums[0] - (1*3);
      break;

    default:  break;
  }
}
