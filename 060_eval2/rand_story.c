#include "rand_story.h"

// Check the number of underscore, it should be even number
void checkUnderScore(FILE * f) {
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    /*char * firstLabl = strchr(line, '_');
    
    if (firstLabl == NULL) {
      free(line);
      fclose(f);
      fprintf(stderr, "No '_' in the line!");
      exit(EXIT_FAILURE);
    }
    */

    // Count and check the number
    int countLabl = 0;
    for (size_t i = 0; line[i] != '\0'; i++) {
      if (line[i] == '_') {
        countLabl++;
      }
    }
    if (countLabl % 2 != 0) {
      free(line);
      fclose(f);
      fprintf(stderr, "Wrong number of '_'!");
      exit(EXIT_FAILURE);
    }
  }
  free(line);
}

// Find the index of category if it exsits, otherwise return -1
int findExistCat(char * category, catarray_t * catArr) {
  for (size_t i = 0; i < catArr->n; i++) {
    if (strcmp(category, catArr->arr[i].name) == 0) {
      return i;
    }
  }
  return -1;
}

int countSpace(char * str) {
  int count = 0;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ') {
      count++;
    }
  }
  free(str);
  return count;
}

int isValidNum(char * str) {
  char * endptr = NULL;
  unsigned long num = strtoul(str, &endptr, 10);
  if (num < 1 && *endptr == '\0') {
    return 0;
  }
  if (*endptr != '\0') {
    return 0;
  }
  return 1;
}

// Parse the story and replace the word, print the whole story
void parseStory(FILE * f, catarray_t * catArr, int allowReuse) {
  size_t sz = 0;
  char * line = NULL;
  //char * arr = NULL;

  checkUnderScore(f);
  rewind(f);

  // Specialize for step1
  if (catArr == NULL) {
    while (getline(&line, &sz, f) >= 0) {
      char * curr = line;
      while (strchr(curr, '_') != NULL) {
        // If there is no underscore, then directly print the whole line
        if (strchr(line, '_') == NULL) {
          break;
        }
        // Locate the blank, preparing for replacing it
        char * blankStart = strchr(curr, '_');
        char * blankEnd = strchr(blankStart + 1, '_');
        // print all stuffs before the blank
        while (*curr != '_' && *curr != '\n') {
          printf("%c", *curr);
          curr++;
        }
        // Save stuffs as category between two underscore, then print
        char * category = strndup(blankStart + 1, blankEnd - blankStart - 1);
        const char * word = chooseWord(category, catArr);
        printf("%s", word);
        // Move on for following dealing
        curr = blankEnd + 1;
        free(category);
      }
      // Since there is no underscore left, just print the left string
      printf("%s", curr);
    }
    free(line);
  }
  // For step3 & step4
  else {
    // use preUsed to track the previous used words
    category_t * preUsed = malloc(sizeof(*preUsed));
    preUsed->n_words = 0;
    preUsed->name = NULL;
    preUsed->words = NULL;
    // Basically the same thing
    while (getline(&line, &sz, f) >= 0) {
      char * curr = line;
      while (strchr(curr, '_') != NULL) {
        char * blankStart = strchr(curr, '_');
        char * blankEnd = strchr(blankStart + 1, '_');
        while (*curr != '_' && *curr != '\n') {
          printf("%c", *curr);
          curr++;
        }

        char * category = strndup(blankStart + 1, blankEnd - blankStart - 1);
        // Check the category, if it is valid integer, then it allow reuse
        //char * endptr = NULL;
        // must be positive integer
        if (isValidNum(category)) {
          // it should within the range
          size_t num = strtoul(category, NULL, 10);
          //size_t len = blankEnd - blankStart;
          /*char * curBlank = blankStart + 1;
          while (curBlank != blankEnd - 1) {
            if (*curBlank - '0' < 0 || *curBlank > 9) {
              num = 0;
              break;
            }
            curBlank++;
          }
          free(curBlank);*/
          if (num > preUsed->n_words) {
            fclose(f);
            free(category);
            free(line);
            fprintf(stderr, "Wrong given integer, outof Index!");
            exit(EXIT_FAILURE);
          }
          const char * word = preUsed->words[preUsed->n_words - num];
          printf("%s", word);
          trackPreUsed(preUsed, 0, word, catArr, 1);
        }
        // Check if it exist in the catarray, whether it allows reuse depends on the option
        else if (findExistCat(category, catArr) >= 0) {
          // find the index in catarr
          int index = findExistCat(category, catArr);
          const char * word = chooseWord(category, catArr);
          printf("%s", word);
          trackPreUsed(preUsed, index, word, catArr, allowReuse);
        }
        // Other situations are not allowed
        else {
          fclose(f);
          free(line);
          fprintf(stderr, "Wrong category string!");
          exit(EXIT_FAILURE);
        }
        free(category);
        curr = blankEnd + 1;
      }
      printf("%s", curr);
    }
    free(line);
    if (preUsed != NULL) {
      for (size_t i = 0; i < preUsed->n_words; i++) {
        free(preUsed->words[i]);
      }
      free(preUsed->words);
    }
    free(preUsed);
  }
}

// Need to free(line)
// Check the colon number, it should only contains one
void checkColon(FILE * f) {
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    char * firstCol = strchr(line, ':');
    if (firstCol == NULL) {
      free(line);
      fclose(f);
      fprintf(stderr, "No colon! Wrong format!");
      exit(EXIT_FAILURE);
    }
    char * otherCol = firstCol + 1;
    if (strchr(otherCol, ':') != NULL) {
      free(line);
      fclose(f);
      fprintf(stderr, "More than one colon! Wrong format!");
      exit(EXIT_FAILURE);
    }
  }
  free(line);
}

// Parse the Category name
char * parseCatName(char * line) {
  char * colon = strchr(line, ':');
  char * catName = strndup(line, colon - line);
  return catName;
}

// Parse the words
char * parseWord(char * line) {
  char * colon = strchr(line, ':');
  char * nullTer = strchr(line, '\0');
  // Need to think how to count the length
  size_t wordLen = nullTer - 1 - colon - 1;
  char * word = strndup(colon + 1, wordLen);
  return word;
}

// Store category name and words in the catarry struct for future use
void storeInCatArr(catarray_t * catArr, char * catName, char * word) {
  for (size_t i = 0; i < catArr->n; i++) {
    if (strcmp(catName, catArr->arr[i].name) == 0) {
      free(catName);
      catArr->arr[i].words =
          realloc(catArr->arr[i].words,
                  (catArr->arr[i].n_words + 1) * sizeof(*catArr->arr[i].words));
      catArr->arr[i].words[catArr->arr[i].n_words] = word;
      catArr->arr[i].n_words++;
      return;
    }
  }
  catArr->arr = realloc(catArr->arr, (catArr->n + 1) * sizeof(*catArr->arr));
  catArr->arr[catArr->n].n_words = 1;
  catArr->arr[catArr->n].name = catName;
  catArr->arr[catArr->n].words = malloc(sizeof(*catArr->arr[catArr->n].words));
  *catArr->arr[catArr->n].words = word;
  catArr->n++;
}

// Parse the inputfile for category and words
catarray_t * parseWordFile(FILE * f) {
  char * line = NULL;
  size_t sz = 0;

  catarray_t * catArr = malloc(sizeof(*catArr));
  catArr->n = 0;
  catArr->arr = NULL;

  checkColon(f);
  rewind(f);

  while (getline(&line, &sz, f) >= 0) {
    char * catName = parseCatName(line);
    char * word = parseWord(line);
    storeInCatArr(catArr, catName, word);
  }
  free(line);
  return catArr;
}

// Free the catarray when finishing using it
void freeCatArr(catarray_t * catArr) {
  if (catArr != NULL) {
    for (size_t i = 0; i < catArr->n; i++) {
      for (size_t j = 0; j < catArr->arr[i].n_words; j++) {
        free(catArr->arr[i].words[j]);
      }
      free(catArr->arr[i].name);
      free(catArr->arr[i].words);
    }
    free(catArr->arr);
    free(catArr);
  }
}
