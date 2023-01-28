#include "rand_story.h"

// Check the number of underscore, it should be even number
void checkBlank(FILE * f) {
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    // Allow that a line do not contain any blank
    /*char * firstLabl = strchr(line, '_');
    
    if (firstLabl == NULL) {
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
      fprintf(stderr, "Wrong number of '_'!");
      exit(EXIT_FAILURE);
    }
  }
  free(line);
}

// Find the index of category in the catArr
int findCatIndex(char * category, catarray_t * catArr) {
  for (size_t i = 0; i < catArr->n; i++) {
    if (strcmp(category, catArr->arr[i].name) == 0) {
      return i;
    }
  }
  return -1;
}

// Update the preUsed to store the used words
void updateUsed(const char * word, category_t * preUsed) {
  preUsed->words =
      realloc(preUsed->words, (preUsed->n_words + 1) * sizeof(*preUsed->words));
  preUsed->words[preUsed->n_words++] = strndup(word, strlen(word));
}

// Update the catArr to delete the used words
void updateCatArr(char * category, const char * word, catarray_t * catArr, int index) {
  size_t delete = 0;
  index = findCatIndex(category, catArr);
  for (size_t i = 0; i < catArr->arr[index].n_words; i++) {
    if (strcmp(word, catArr->arr[index].words[i]) == 0) {
      delete = i;
      break;
    }
  }

  //free(catArr->arr[index].words[delete]);
  //catArr->arr[index].n_words--;
  for (size_t i = delete; i < catArr->arr[index].n_words - 1; i++) {
    catArr->arr[index].words[i] = catArr->arr[index].words[i + 1];
  }
  free(catArr->arr[index].words[catArr->arr[index].n_words - 1]);
  catArr->arr[index].n_words--;
}

// chooseWord from based on all the choice
const char * chooseReuseWord(char * category,
                             catarray_t * catArr,
                             category_t * preUsed,
                             int allowReuse) {
  if (catArr == NULL) {
    return chooseWord(category, catArr);
  }
  char * endptr = NULL;
  size_t num = strtoul(category, &endptr, 10);
  const char * word = NULL;
  // Check if it is positive integer
  if (num > 0 && *endptr == '\0') {
    if (num > preUsed->n_words) {
      fprintf(stderr, "Wrong given integer, out of bound!");
      exit(EXIT_FAILURE);
    }
    // Record the used
    const char * nword = preUsed->words[preUsed->n_words - num];
    updateUsed(nword, preUsed);
    return nword;
  }
  // Check if  we can find the category in the catArr
  else if (findCatIndex(category, catArr) >= 0) {
    const char * mword = chooseWord(category, catArr);
    //int index = findCatIndex(category, catArr);
    updateUsed(mword, preUsed);
    if (allowReuse == 0) {
      // updateCatArr(category, mword, catArr, index);
    }
    return mword;
  }
  else {
    fprintf(stderr, "Wrong format of category!");
    exit(EXIT_FAILURE);
  }
  //printf("The word is %s", word);
  return word;
}

// Parse each line for future line
char * parseLine(char * line, catarray_t * catArr, category_t * preUsed, int allowReuse) {
  char * curr = line;
  // if there is no underscore in current line
  if (strchr(line, '_') == NULL) {
    return line;
  }

  // Use two variable to track the result string index and length, for realloc and storing
  size_t resultIdx = 0;
  size_t resultLen = 0;
  char * result = malloc(sizeof(*result));
  // While loop deal with the string with blank
  while (strchr(curr, '_') != NULL) {
    // locate the next blank
    char * blankStart = strchr(curr, '_');
    char * blankEnd = strchr(blankStart + 1, '_');
    // calculate the length for parse
    size_t lineLen = blankStart - curr;
    size_t blankLen = blankEnd - blankStart - 1;
    char * blankToWord = strndup(blankStart + 1, blankLen);
    const char * word;
    //if (catArr == NULL) {
    //word = chooseWord(blankToWord, catArr);
    //}
    //else {
    word = chooseReuseWord(blankToWord, catArr, preUsed, allowReuse);
    //printf("the word is %s\n", word);
    //}
    //free(blankToWord);

    // copy the following content in the result
    size_t wordLen = strlen(word);
    size_t lineBefBlank = lineLen + wordLen;
    resultLen += lineBefBlank;
    result = realloc(result, (resultLen) * sizeof(*result));
    while (*curr != '_' && *curr != '\n') {
      result[resultIdx++] = *curr;
      curr++;
    }
    for (size_t i = 0; i < wordLen; i++) {
      result[resultIdx++] = word[i];
    }
    free(blankToWord);
    curr = blankEnd + 1;
  }
  // Out of loop, deal with the left string without blank
  size_t lineLeftLen = strlen(curr);

  result = realloc(result, (resultLen + lineLeftLen + 1) * (*result));
  for (size_t i = 0; curr[i] != '\0'; i++) {
    result[resultIdx++] = curr[i];
  }

  result[resultIdx] = '\0';
  return result;
}

void parseStory(FILE * f, catarray_t * catArr, int allowReuse) {
  size_t sz = 0;
  char * line = NULL;
  //char * arr = NULL;

  checkBlank(f);
  rewind(f);

  // Use preUsed to record used word
  category_t * preUsed = malloc(sizeof(*preUsed));
  preUsed->name = NULL;
  preUsed->words = NULL;
  preUsed->n_words = 0;

  // Parse line and print the line
  while (getline(&line, &sz, f) >= 0) {
    char * str = parseLine(line, catArr, preUsed, allowReuse);
    printf("%s", str);
    if (strchr(line, '_') != NULL) {
      free(str);
    }
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

// Check the colon number, it should only contains one
void checkColon(FILE * f) {
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    char * firstCol = strchr(line, ':');
    if (firstCol == NULL) {
      fprintf(stderr, "No colon! Wrong format!");
      exit(EXIT_FAILURE);
    }
    char * otherCol = firstCol + 1;
    if (strchr(otherCol, ':') != NULL) {
      fprintf(stderr, "Wrong number of colon!");
      exit(EXIT_FAILURE);
    }
  }
  free(line);
}

// Parse the Category name
char * parseCatName(char * str) {
  char * colon = strchr(str, ':');
  size_t catNameLen = colon - str;
  char * catName = malloc((catNameLen + 1) * sizeof(*catName));
  size_t i = 0;
  for (; str[i] != ':'; i++) {
    catName[i] = str[i];
  }
  catName[i] = '\0';
  return catName;
}

// Parse the words
char * parseWord(char * str) {
  char * nullTer = strchr(str, '\0');
  // Need to think how to count the length, end with '\n' or no new line?
  size_t wordLen = nullTer - 1 - str;
  char * word = malloc((wordLen + 1) * sizeof(*word));
  size_t i = 0;
  for (; str[i] != '\n'; i++) {
    word[i] = str[i];
  }
  word[i] = '\0';
  return word;
}

// Store category name and words in the catarry struct for future use
void storeInCatArr(char * catName, char * word, catarray_t * catArr) {
  // Go through the current catArr to check if there is the same category
  for (size_t i = 0; i < catArr->n; i++) {
    // If there is the same category
    if (strcmp(catName, catArr->arr[i].name) == 0) {
      // Realloc place for arr[i].words and add a word in the newly realloc place
      catArr->arr[i].words =
          realloc(catArr->arr[i].words,
                  (catArr->arr[i].n_words + 1) * sizeof(*catArr->arr[i].words));
      catArr->arr[i].words[catArr->arr[i].n_words] = word;
      catArr->arr[i].n_words++;
      // Important! valgrind will report error, strcmp
      free(catName);
      return;
    }
  }
  // Do not find the same category name, then create a new catArr->arr
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
    // Try with strtok, but there would be memory leak problems, why?
    char * catName = parseCatName(line);
    char * colon = strchr(line, ':');
    char * word = parseWord(colon + 1);
    storeInCatArr(catName, word, catArr);
  }
  free(line);
  return catArr;
}

// Free the catarray when finishing using it
void freeCatArr(catarray_t * catArr) {
  for (size_t i = 0; i < catArr->n; i++) {
    for (size_t j = 0; j < catArr->arr[i].n_words; j++) {
      free(catArr->arr[i].words[j]);
    }
    // It is necessary as the words is created using malloc
    free(catArr->arr[i].name);
    free(catArr->arr[i].words);
  }
  free(catArr->arr);
  free(catArr);
}
