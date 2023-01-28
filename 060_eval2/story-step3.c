#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Wrong command line arguments!");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  FILE * template = fopen(argv[2], "r");

  if (f == NULL || template == NULL) {
    fprintf(stderr, "No file read!");
    exit(EXIT_FAILURE);
  }

  catarray_t * catArr = parseWordFile(f);

  parseStory(template, catArr, 1);
  freeCatArr(catArr);

  if (fclose(f) != 0 || fclose(template) != 0) {
    fprintf(stderr, "Fail to close the file!");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
