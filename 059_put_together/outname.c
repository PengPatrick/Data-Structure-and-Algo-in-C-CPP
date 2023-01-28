#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * str = ".counts";
  size_t newStrLen = strlen(inputName) + strlen(str) + 1;
  char * newStr = malloc(newStrLen * sizeof(newStr));
  strcpy(newStr, inputName);
  strcpy(newStr + strlen(inputName), str);
  return newStr;
}
