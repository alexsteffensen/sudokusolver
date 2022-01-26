#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "debug.h"
#include "sudoku.h"
#include "solve.h"
#include "interpreter.h"

#define PATH_MAX 5000


int main(void) {
  block blocks[NUM_OF_BLOCKS];

  char buffer[PATH_MAX];
  char *input_file_dir = "/input.txt";
  char *working_dir = getcwd(buffer, sizeof(buffer));
  char *cmake_dir = "/cmake-build-debug";
  char *condition = strstr(working_dir, cmake_dir);

  if (condition != NULL)
    *condition = '\0';

  char *input_dir = strcat(working_dir, input_file_dir);
  FILE *sudoku_data = fopen(input_dir , "r");

  if (sudoku_data == NULL) {
    printf("Failed to load input file. \n");
    exit(0);
  }

  read_file(blocks, sudoku_data);
  fclose(sudoku_data);

  printf("The sudoku before solving \n");
  print_sudoku(blocks);

  solve_sudoku(blocks);

  printf("The sudoku after solving it \n");
  print_sudoku(blocks);

  return EXIT_SUCCESS;
}
