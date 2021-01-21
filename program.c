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

int main(void) {
  block blocks[NUM_OF_BLOCKS];
  int i, j = 0;
  FILE *sudoku_data = fopen("input.txt" , "r");

  
  for (i = 0; i < NUM_OF_BLOCKS; i++) {
    blocks[i].num = i + 1;
    for(j = 0; j < NUM_OF_NUMS; j++)
      blocks[i].numbers[j] = j + 1;
    printf("HELlO %d \n", blocks[i].numbers[i]);
  }

  /*read_file(blocks, sudoku_data);*/

  print_sudoku(blocks);

  return EXIT_SUCCESS;
}
/*
void read_file(block *blocks, FILE *data) {
  char line[MAX_LINE_LEN], first_char;
  int i, j = 0, counter = 0;

  for (i = 0; i < NUM_OF_LINES; i++) {
    if (counter > 1)
      j += 3;

    fgets(line, MAX_LINE_LEN, data);
    sscanf(line, "%c", &first_char);

    if (first_char == '|') {
      sscanf(line, "| %d %d %d | %d %d %d | %d %d %d |",
             blocks);
    }

    else if (first_char == '-') {
      counter++;
      continue;
    }

    else
      continue;
  }

}
*/

void print_sudoku(block *blocks) {
  int i, p, j, k;

  printf("-------------------------\n");
  for(i = 0; i < NUM_OF_BLOCKROWS; i++) {
    
    for (p = 0; p < NUM_OF_BLOCKS/3; p++){
      for(j = 0; j < NUM_OF_NUMS/3; j++) {
        printf("| ");
        for(k = 0; k < NUM_OF_NUMS/3; k++)
          printf("%d ", blocks[(i*3)+j].numbers[(p*3)+k]);
      }
      printf("| \n");
    }
    printf("-------------------------\n");

  }
}



