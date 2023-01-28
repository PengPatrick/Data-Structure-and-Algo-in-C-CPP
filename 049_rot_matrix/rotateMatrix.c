#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "please indicate the input file");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    fprintf(stderr, "count not find the file ");
    return EXIT_FAILURE;
  }

  int c = 0;
  int row = 0;
  int col = 0;
  int count = 0;
  char matrix[10][10];
  while ((c = fgetc(f)) != EOF) {
    if (row < 10) {
      if (c == '\n') {
        if (col != 10) {
          perror("Col number is wrong!");
          exit(EXIT_FAILURE);
        }
        row++;
        col = 0;
      }
      else {
        matrix[col][9 - row] = c;
        col++;
      }
    }
    count++;
    if (count > 110) {
      perror("Exceed contents!");
      exit(EXIT_FAILURE);
    }
  }
  if (row <= 9) {
    perror("Row number is wrong!");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}
