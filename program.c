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

  read_file(blocks, sudoku_data);

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

}


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



