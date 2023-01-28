#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use

/* For parsing story and checking */

// check the format of underscore, for blank
void checkUnderScore(FILE * f);

// track the previous used words and keep updating
// Input:      category_t *preUsed for previous used words
//             int index, for matching exsisting category & words
//             const char *word, the ouput of chooseWord function, also for printing
//             catarray_t *catArr, storing the category & words
//             int allowReuse, for choosing whether allow reuse or not, 1 for allowing, 0 for banned
void trackPreUsed(category_t * preUsed,
                  int index,
                  const char * word,
                  catarray_t * catArr,
                  int allowReuse);

// find the index in the catarray that has used name
// return the index, if there is no index, return -1
int findExistCat(char * category, catarray_t * catArr);

int isValidNum(char * str);
// parsse the story template then print the story with propriate words, with option to reuse or not
// Input:     FILE *f for story template
//            catarray_t *catArr for storing category and words from words file
void parseStory(FILE * f, catarray_t * catArr, int allowReuse);

/* For parsing category and word */

// check the number of colon, for words file format checking
void checkColon(FILE * f);
// store the category and words in a struct for future use
void storeInCatArr(catarray_t * catArr, char * catName, char * word);
// parse category name, string
char * parseCatName(char * line);
// parse word, stirng
char * parseWord(char * line);
// parse the word file to get category and words
catarray_t * parseWordFile(FILE * f);
// free the struct storing the category and words when finishing using it
void freeCatArr(catarray_t * catArr);

#endif
