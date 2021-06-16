#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_BLOCKS 9
#define NUM_OF_NUMS 9
#define MAX_LINE_LEN 100
#define NUM_OF_BLOCKROWS 3

typedef struct block{
  int numbers[NUM_OF_NUMS];
}block;

void read_file(block *blocks, FILE *data);
void print_sudoku(block *blocks);
void solve_sudoku(block *blocks);
int find_number(block *blocks);
int check_horizontal(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
int check_vertical(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
void find_num_hor(int *pos_calc);
void find_num_ver(int *block_calc);
int check_block(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
int check_number(int *temp_number_arr, int *arr_pos, int number);
void insert_number(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
void print_array(int *arr);

int exclusion_method(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
void find_numbers(int *temp_number_arr, int *arr_pos, int *search_nums);
void find_remaining_pos(block *blocks, int block_num, int pos_num, int* remain_pos);
int check_positions(block *blocks, int block_num, int *remain_pos, int arr_len, int num);
int check_horizontal_exclusion(block *blocks, int block_num, int remain_pos, int arr_len, int num);
int check_vertical_exclusion(block *blocks, int block_num, int remain_pos, int arr_len, int num);
int check_pos_exclusion(block *blocks, int block_num, int pos_num, int num);
int find_pos_num(block *blocks, int block_num, int pos_num);

int main(void) {
  block blocks[NUM_OF_BLOCKS];

  printf("Hello team");

  FILE *sudoku_data = fopen("input.txt" , "r");

  if (sudoku_data == NULL) {
    perror("Failed: ");
    exit(1);
  }

  read_file(blocks, sudoku_data);
  fclose(sudoku_data);

  printf("SUDOKU BEFORE SOLVING \n");
  print_sudoku(blocks);

  solve_sudoku(blocks);

  printf("SUDOKU AFTER SOLVING \n");
  print_sudoku(blocks);

  return EXIT_SUCCESS;
}

void read_file(block *blocks, FILE *data) {
  char line[MAX_LINE_LEN], first_char;
  int i = -1, p = 0, sudoku_read = 0;

  while (!sudoku_read) {

    fgets(line, MAX_LINE_LEN, data);
    sscanf(line, "%c", &first_char);

    if (first_char == '|') {
      sscanf(line, "| %d %d %d | %d %d %d | %d %d %d | ",
             &blocks[(i*3)].numbers[(p*3)], &blocks[(i*3)].numbers[(p*3)+1], &blocks[(i*3)].numbers[(p*3)+2],
             &blocks[(i*3)+1].numbers[(p*3)], &blocks[(i*3)+1].numbers[(p*3)+1], &blocks[(i*3)+1].numbers[(p*3)+2],
             &blocks[(i*3)+2].numbers[(p*3)], &blocks[(i*3)+2].numbers[(p*3)+1], &blocks[(i*3)+2].numbers[(p*3)+2]);
      p++;
    }

    else if (first_char == '-') {
      i++;
      p = 0;
      if (i > 2)
        sudoku_read = 1;
      continue;
    }
    else
      continue;
  }
  for (i = 0; i < NUM_OF_BLOCKS; i++) {
    printf("Block %d [", i);
    for (p = 0; p < NUM_OF_NUMS; p++){
      printf(" %d ", blocks[i].numbers[p]);
    }
    printf("]\n");
  }
}

void print_sudoku(block *blocks) {
  int i, p, j, k, number;

  printf("-------------------------\n");
  for(i = 0; i < NUM_OF_BLOCKROWS; i++) {
    for (p = 0; p < NUM_OF_BLOCKS/3; p++){
      for(j = 0; j < NUM_OF_NUMS/3; j++) {
        printf("| ");
        for(k = 0; k < NUM_OF_NUMS/3; k++) {
          number = blocks[(i*3)+j].numbers[(p*3)+k];

          if (number)
            printf("%d ", number);
          else
            printf("  ");
        }
      }
      printf("| \n");
    }
    printf("-------------------------\n");

  }
}

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

void print_array(int *arr) {
  int i;

  for (i = 0; i < NUM_OF_NUMS; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
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



