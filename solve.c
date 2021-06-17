
#include "solve.h"

/* Skal løse sudokuen */
void solve_sudoku(block *blocks) {
  int number_found;

  do {
    number_found = find_number(blocks);
    printf("KØRER\n");
  } while (number_found);
  printf("KØRER UD\n");
}

/* Skal bare finde et nyt nummer der kan skrives i sudokuen*/
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
        printf("--------------------LEDER EFTER NÆSTE TAL-----------------------\n");
        for (k = 0; k < NUM_OF_NUMS; k++){
          temp_number_arr[k] = -1;
        }
        arr_pos = 0;
        printf("Array resetting...\n");
        printf("Leder efter et tal til blok %d pos %d\n", i, j);
        if (check_block(blocks, temp_number_arr, i, j, &arr_pos) ||
            check_horizontal(blocks, temp_number_arr, i, j, &arr_pos) ||
            check_vertical(blocks, temp_number_arr, i, j, &arr_pos)  ||
            exclusion_method(blocks, temp_number_arr, i, j, &arr_pos)){
          number_found = 1;
          return 1;
        }

      }
      if (j < NUM_OF_NUMS-1){ /* Er alle tal i blokken tjekket? */
        j++;  /* nej */
      }
      else
        break; /* ja */
    }

    if (i < NUM_OF_BLOCKS-1){ /* Er alle blokkene blevet tjekket? */
      i++; /* nej */
      continue;
    }
    else
      break; /* ja */
  }


  return 0;
}

/* Skal tjekke de tal der er i blokken */
int check_block(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int i, current_number;
  printf("tjekker blokken.\n");
  for (i = 0; i < NUM_OF_NUMS; i++){
    current_number = blocks[block_num].numbers[i];

    if (current_number > 0 && current_number < 10 && check_number(temp_number_arr, arr_pos, current_number)){
      temp_number_arr[*arr_pos] = current_number;
      ++(*arr_pos);
      printf("Arr_pos has been incremented to: %d\n", *arr_pos);
      if (*arr_pos == (NUM_OF_NUMS - 1)){
        print_array(temp_number_arr);
        insert_number(blocks, temp_number_arr, block_num, pos_num, arr_pos);
        return 1;
      }
      else
        continue;
    }
  }
  print_array(temp_number_arr);
  return 0;
}

/* Skal tjekke tallene er ligger vandret med det felt der søges med */
int check_horizontal(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int pos_calc[3];
  int block_calc[3];
  int i, j, current_number;

  printf("Tjekker horizontalt\n");
  pos_calc[0] = pos_num;
  block_calc[0] = block_num;

  find_num_hor(pos_calc);
  find_num_hor(block_calc);

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      current_number = blocks[block_calc[i]].numbers[pos_calc[j]];
      printf("block_calc: %d, pos_cal: %d, tallet: %d \n", block_calc[i], pos_calc[j], current_number);
      if (current_number > 0 && current_number < 10 && check_number(temp_number_arr, arr_pos, current_number)){
        temp_number_arr[*arr_pos] = current_number;
        ++(*arr_pos);
        printf("Arr_pos has been incremented to: %d \n", *arr_pos);
        if (*arr_pos == (NUM_OF_NUMS - 1)){
          print_array(temp_number_arr);
          insert_number(blocks, temp_number_arr, block_num, pos_num, arr_pos);
          return 1;
        }
        else
          continue;
      }
    }
  }
  print_array(temp_number_arr);
  return 0;
}

/* Skal tjekke tallene er ligger lodret med det felt der søges med */
int check_vertical(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int pos_calc[3];
  int block_calc[3];
  int i, j;
  int current_number;
  printf("tjekker veritkalt\n");
  pos_calc[0] = pos_num;
  block_calc[0] = block_num;

  find_num_ver(pos_calc);
  find_num_ver(block_calc);

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      current_number = blocks[block_calc[i]].numbers[pos_calc[j]];
      printf("block_calc: %d, pos_cal: %d, tallet: %d \n", block_calc[i], pos_calc[j], current_number);
      if (current_number > 0 && current_number < 10 && check_number(temp_number_arr, arr_pos, current_number)){
        temp_number_arr[*arr_pos] = current_number;
        ++(*arr_pos);
        printf("Arr_pos has been incremented to: %d\n", *arr_pos);
        if (*arr_pos == (NUM_OF_NUMS - 1)){
          print_array(temp_number_arr);
          insert_number(blocks, temp_number_arr, block_num, pos_num, arr_pos);
          return 1;
        }
        else
          continue;
      }
    }
  }
  printf("arr_pos: %d \n", *arr_pos);
  print_array(temp_number_arr);
  return 0;

}

int check_number(int *temp_number_arr, int *arr_pos, int number) {
  int i;

  for (i = 0; i < *arr_pos; i++){
    if (number == temp_number_arr[i])
      return 0;
  }
  return 1;
}



void insert_number(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos) {
  int num_being_checked = 1;
  int num_placed = 0;
  int i;

  while (!num_placed){
    for (i = 0; i < *arr_pos; i++){

      if (num_being_checked == temp_number_arr[i]){
        break;
      }
      else if (i == *arr_pos-1){
        blocks[block_num].numbers[pos_num] = num_being_checked;
        printf("Første tal sættes i: %d, og placeres i blok: %d position %d\n", num_being_checked, block_num, pos_num);
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



