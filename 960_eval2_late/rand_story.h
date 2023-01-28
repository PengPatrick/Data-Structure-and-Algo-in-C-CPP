#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use

/* For parsing story and checking */

// check the format of blank
void checkBlank(FILE * f);

// check the blank format
void checkBlank(FILE * f);

// find the index of category
int findCatIndex(char * category, catarray_t * catArr);

// update preUsed to record
void updateUsed(const char * word, category_t * preUsed);

// update catArr, delete used
void updateCatArr(char * category, const char * word, catarray_t * catArr, int index);

// choose Words
const char * chooseReuseWord(char * category,
                             catarray_t * catArr,
                             category_t * preUsed,
                             int allowReuse);

// parse each line
char * parseLine(char * line, catarray_t * catArr, category_t * preUsed, int allowReuse);

// parsse the story template then print the story with propriate words
//void parseStory(FILE * f, catarray_t * catArr);
void parseStory(FILE * f, catarray_t * catArr, int allowReuse);

/* For parsing category and word */

// check the number of colon, for words file format checking
void checkColon(FILE * f);
// store the category and words in a struct for future use
void storeInCatArr(char * catName, char * word, catarray_t * catArr);
// parse category name, string
char * parseCatName(char * line);
// parse word, stirng
char * parseWord(char * line);
// parse the word file to get category and words
catarray_t * parseWordFile(FILE * f);
// free the struct storing the category and words when finishing using it
void freeCatArr(catarray_t * catArr);

#endif
