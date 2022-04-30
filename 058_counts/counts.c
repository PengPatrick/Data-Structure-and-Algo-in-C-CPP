#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t *counts = malloc(sizeof(*counts));
  counts->countArr = NULL;
  counts->numKnown = 0;
  counts->numUnknown = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if(name == NULL){
    c->numUnknown++;
    return;
  }
  int num = c->numKnown;
  for(int i = 0; i < num; i++){
    if(strcmp(c->countArr[i]->name, name) == 0){
      c->countArr[i]->num++;
      return;
    }
  }

  //special case for no numknown
  int len = strlen(name);
  num += 1;
  c->numKnown = num;
  c->countArr = realloc(c->countArr, num * sizeof(*c->countArr));
  one_count_t *one_count = malloc(sizeof(*one_count));
  one_count->name = malloc((len+1) * sizeof(*one_count->name));
  strcpy(one_count->name, name);
  one_count->num = 1;
  c->countArr[num-1] = one_count;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(int i = 0; i < c->numKnown; i++){
    fprintf(outFile, "%s: %d\n", c->countArr[i]->name, c->countArr[i]->num);
  }
  if(c->numUnknown > 0){
    fprintf(outFile, "<unknown>: %d\n", c->numUnknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(int i = 0; i < c->numKnown; i++){
    free(c->countArr[i]->name);
    free(c->countArr[i]);
  }
  free(c->countArr);
  free(c);
}
