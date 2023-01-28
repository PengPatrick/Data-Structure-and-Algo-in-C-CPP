#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "Wrong command line arguments!");
    exit(EXIT_FAILURE);
  }
  else if (argc == 4 && strcmp("-n", argv[1]) != 0) {
    fprintf(stderr, "Wrong option! should use '-n' for the first command line argument!");
    exit(EXIT_FAILURE);
  }

  char * words = NULL;
  char * template = NULL;
  int allowReuse = 1;

  if (argc == 3) {
    words = argv[1];
    template = argv[2];
  }
  else if (argc == 4) {
    words = argv[2];
    template = argv[3];
    allowReuse = 0;
  }

  FILE * wordsFile = fopen(words, "r");
  FILE * storyFile = fopen(template, "r");

  if (wordsFile == NULL || storyFile == NULL) {
    fprintf(stderr, "No file read!");
    exit(EXIT_FAILURE);
  }

  catarray_t * catArr = parseWordFile(wordsFile);
  parseStory(storyFile, catArr, allowReuse);

  freeCatArr(catArr);

  if (fclose(wordsFile) != 0 || fclose(storyFile) != 0) {
    fprintf(stderr, "Fail to close file!");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
