#include "exclusion.h"

int exclusion_method(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int arr_len = NUM_OF_NUMS - *arr_pos;
  int search_nums[arr_len];
  int remain_pos_len = find_pos_num(blocks, block_num, pos_num);
  int remain_pos[remain_pos_len];
  int i, j;


  printf("**********Udelukkelses metoden starter********** \n");

  find_numbers(temp_number_arr, arr_pos, search_nums);

  printf("Pos arr len: %d \n", remain_pos_len);

  printf("arr_len %d og arr_pos %d \n", arr_len, *arr_pos);

  printf("Tallene der skal søges igennem er [");
  for (j = 0; j < arr_len; j++){
    printf("%d, ", search_nums[j]);
  }
  printf("]\n");


  find_remaining_pos(blocks, block_num, pos_num, remain_pos);

  printf("Positionerne der skal søges igennem er [");
  for (j = 0; j < remain_pos_len; j++){
    printf("%d, ", remain_pos[j]);
  }
  printf("]\n");

  /*looping over the numbers that should be checked for*/
  for (i = 0; i < arr_len; i++) {
    printf("!!!!!!!!!KIGGER PÅ NUMMER %d \n", search_nums[i]);
    if (check_positions(blocks, block_num, remain_pos, remain_pos_len, search_nums[i])){
      printf("Indsætter tallet: %d ind i blok: %d pos: %d", search_nums[i], block_num, pos_num);
      blocks[block_num].numbers[pos_num] = search_nums[i];
      return 1;
    }
  }
  return 0;
}

int find_pos_num(block *blocks, int block_num, int pos_num) {
  int i;
  int arr_len = 0;

  for (i = 0; i < NUM_OF_NUMS; i++){
    int current_pos_value = blocks[block_num].numbers[i];
    if (i == pos_num)
      continue;
    else if (current_pos_value == 0)
      arr_len++;
  }
  return arr_len;
}

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
      printf("Added position %d \n", pos);
      remain_pos[j] = pos;
      j++;
    }
  }
}

/* Skal holde styr på om den position der tjekkes kan få tallet sat ind eller ej */
int check_positions(block *blocks, int block_num, int *remain_pos, int arr_len, int num) {
  int i;

  for (i = 0; i < arr_len; i++){
    printf("*********TJekker posisiton %d ********", remain_pos[i]);
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

int check_horizontal_exclusion(block *blocks, int block_num, int checking_pos, int arr_len, int num) {
  int pos_calc[3];
  int block_calc[3];
  int i, j;

  printf("Tjekker horizontalt (udlukkelses)\n");

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

int check_vertical_exclusion(block *blocks, int block_num, int checking_pos, int arr_len, int num) {
  int pos_calc[3];
  int block_calc[3];
  int i, j;

  printf("Tjekker vertikalt (udlukkelses)\n");

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

int check_pos_exclusion(block *blocks, int block_num, int pos_num, int num) {
  int current_number = blocks[block_num].numbers[pos_num];
  printf("block_calc: %d, pos_cal: %d, tallet: %d \n", block_num, pos_num, current_number);
  if (current_number == num)
    return 1;
  return 0;
}

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
