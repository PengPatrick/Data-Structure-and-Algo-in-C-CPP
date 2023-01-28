#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong command line arguments!");
    exit(EXIT_FAILURE);
  }

  FILE * template = fopen(argv[1], "r");
  if (template == NULL) {
    fprintf(stderr, "No file read!");
    exit(EXIT_FAILURE);
  }

  parseStory(template, NULL, 1);

  if (fclose(template) != 0) {
    fprintf(stderr, "Fail to close the file!");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
