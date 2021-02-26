#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_BLOCKS 9
#define NUM_OF_NUMS 9
#define MAX_LINE_LEN 100
#define NUM_OF_LINES 16
#define NUM_OF_BLOCKROWS 3

typedef struct block{
  int numbers[NUM_OF_NUMS];
  int num;
}block;


void read_file(block *blocks, FILE *data);
void print_sudoku(block *blocks);
void solve_sudoku(block *blocks);
int find_number(block *blocks);
int check_horizontal(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
int check_vertical(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
void find_block_num_hor(int block_num, int *block_calc);
void find_pos_num_hor(int pos_num, int *pos_calc);
void find_block_num_ver(int block_num, int *block_calc);
void find_pos_num_ver(int pos_num, int *pos_calc);
int check_block(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
int check_number(int *temp_number_arr, int *arr_pos, int number);
void insert_number(block *blocks, int *temp_number_arr, int block_num, int pos_num, int *arr_pos);
void print_array(int *arr);

int main(void) {
  block blocks[NUM_OF_BLOCKS];
  int i, j = 0;
  FILE *sudoku_data = fopen("input.txt" , "r");

  read_file(blocks, sudoku_data);

  printf("SUDOKU BEFORE SOLVING \n");
  print_sudoku(blocks);

  solve_sudoku(blocks);

  printf("SUDOKU AFTER SOLVING \n");
  print_sudoku(blocks);


  return EXIT_SUCCESS;
}

void read_file(block *blocks, FILE *data) {
  char line[MAX_LINE_LEN], first_char;
  int i = -1, p = 0, counter = 0, blockcounter = 0, soduko_read = 0, number;

  while (!soduko_read) {

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
        soduko_read = 1;
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
            check_vertical(blocks, temp_number_arr, i, j, &arr_pos)){
          number_found = 1;
          return 1;
        }
         
      }
      
      if (j < NUM_OF_NUMS) /* Er alle tal i blokken tjekket? */
        j++; /* Nej */
      else
        break; /* ja */
    }
    
    if (i < NUM_OF_BLOCKS) /* Er alle blokkene blevet tjekket? */
      i++; /* nej */
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
  int i, j;
  int current_number;
  printf("Tjekker horizontalt\n");
  pos_calc[0] = pos_num;
  block_calc[0] = block_num;

  find_pos_num_hor(pos_num, pos_calc);
  find_block_num_hor(block_num, block_calc);

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      current_number = blocks[block_calc[i]].numbers[pos_calc[j]];
      printf("block_calc: %d, pos_cal: %d, tallet: %d \n", block_calc[i], pos_calc[j], current_number);
      if (current_number > 0 && current_number < 10 && check_number(temp_number_arr, arr_pos, current_number)){
        temp_number_arr[*arr_pos] = current_number;
        ++(*arr_pos);
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
  int i, j, k, l;
  int current_number;
  printf("tjekker veritkalt ");
  pos_calc[0] = pos_num;
  block_calc[0] = block_num;

  find_pos_num_ver(pos_num, pos_calc);
  find_block_num_ver(block_num, block_calc);

  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      k = block_calc[i];
      l = pos_calc[j];
      current_number = blocks[k].numbers[l];
      printf("block_calc: %d, pos_cal: %d, tallet: %d \n", k, l, current_number);
      if (current_number > 0 && current_number < 10 && check_number(temp_number_arr, arr_pos, current_number)){
        temp_number_arr[*arr_pos] = current_number;
        ++(*arr_pos);
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

int check_number(int *temp_number_arr, int *arr_pos, int number) {
  int i;

  for (i = 0; i < *arr_pos; i++){
    if (number == temp_number_arr[i])
      return 0;
  }
  
  return 1;

}

void find_block_num_hor(int block_num, int *block_calc) {
  switch (block_num % 3) {
  case 0:
    block_calc[1] = block_num + 1;
    block_calc[2] = block_num + 2;
    break;
  
  case 1:
    block_calc[1] = block_num - 1;
    block_calc[2] = block_num + 1;
    break;

  case 2:
    block_calc[1] = block_num - 2;
    block_calc[2] = block_num - 1;
    break;

  default:  break;
  }
}

void find_block_num_ver(int block_num, int *block_calc) {
  switch (block_num / 3) {
  case 0:
    block_calc[1] = block_num + (1*3);
    block_calc[2] = block_num + (2*3);
    break;
  
  case 1:
    block_calc[1] = block_num - (1*3);
    block_calc[2] = block_num + (1*3);
    break;

  case 2:
    block_calc[1] = block_num - (2*3);
    block_calc[2] = block_num - (1*3);
    break;

  default:  break;
  }
}

void find_pos_num_hor(int pos_num, int *pos_calc) {
  switch (pos_num % 3) {
  case 0:
    pos_calc[1] = pos_num + 1;
    pos_calc[2] = pos_num + 2;
    break;
  
  case 1:
    pos_calc[1] = pos_num - 1;
    pos_calc[2] = pos_num + 1;
    break;

  case 2:
    pos_calc[1] = pos_num - 2;
    pos_calc[2] = pos_num - 1;
    break;

  default:  break;
  }
}


void find_pos_num_ver(int pos_num, int *pos_calc) {
  switch (pos_num / 3) {
  case 0:
    pos_calc[1] = pos_num + (1*3);
    pos_calc[2] = pos_num + (2*3);
    break;
  
  case 1:
    pos_calc[1] = pos_num - 3;
    pos_calc[2] = pos_num + 3;
    break;

  case 2:
    pos_calc[1] = pos_num - (2*3);
    pos_calc[2] = pos_num - (1*3);
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
        printf("Første tal sættes i: %d, og placeres i blok: %d position %d", num_being_checked, block_num, pos_num);
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


