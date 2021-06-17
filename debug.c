#include "debug.h"

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

void print_array(int *arr) {
  int i;

  for (i = 0; i < NUM_OF_NUMS; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

