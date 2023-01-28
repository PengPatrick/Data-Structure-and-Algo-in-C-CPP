#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int freqIndex(FILE * f) {
  int c;
  int freq[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      freq[c - 'a']++;
    }
  }

  int index = 0;
  int max = 0;
  for (int i = 0; i < 26; i++) {
    if (freq[i] > max) {
      index = i;
      max = freq[i];
    }
  }

  return index;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of command line arguments");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file");
    return EXIT_FAILURE;
  }

  int key = freqIndex(f);
  key = (key + 'a' - 'e' + 26) % 26;

  fprintf(stdout, "%d\n", key);

  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close the file");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
