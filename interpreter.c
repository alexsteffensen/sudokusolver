#include "interpreter.h"

/* reads the input file with unsolved sudoku */
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
}

