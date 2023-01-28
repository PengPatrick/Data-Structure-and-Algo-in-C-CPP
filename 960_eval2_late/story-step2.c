#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of command line arguments!");
    exit(EXIT_FAILURE);
  }

  FILE * category = fopen(argv[1], "r");
  if (category == NULL) {
    fprintf(stderr, "No file read!");
    exit(EXIT_FAILURE);
  }

  catarray_t * catArr = parseWordFile(category);
  printWords(catArr);

  freeCatArr(catArr);

  if (fclose(category) != 0) {
    fprintf(stderr, "Fail to close the file!");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
