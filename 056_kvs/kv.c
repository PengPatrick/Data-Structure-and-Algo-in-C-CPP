#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void stripNewLine(char * str){
  char * p = strchr(str, '\n');
  if(p != NULL){
    *p = '\0';
  }

}

kvpair_t* findPair(char * str){
  stripNewLine(str);
  char * place = strchr(str, '=');
  if(place == NULL){
    perror("error");
    exit(EXIT_FAILURE);
  }
  kvpair_t * pair = malloc(sizeof(*pair));
  pair->key = NULL;
  pair->value = NULL;
  int rightLen = strlen(place+1);
  int leftLen = strlen(str) - rightLen - 1;
  if(strlen(str) == 0){
    perror("error");
    exit(EXIT_FAILURE);
  }
  
  pair->key = malloc((leftLen + 1) * sizeof(*pair->key));
  pair->value = malloc((rightLen + 1) * sizeof(*pair->value));
  strncpy(pair->key, str, leftLen);
  pair->key[leftLen] = '\0';
 
  strcpy(pair->value, place+1);
  
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
    size_t sz = 0;
  char * line = NULL;
  FILE * f = fopen(fname, "r");
  if (f == NULL){
       fprintf(stderr,"count not find the file ");
       exit(EXIT_FAILURE);
      }
  kvarray_t * kvArr = malloc(sizeof(*kvArr));
  //memset(kvArr, 0, sizeof(*kvArr));
  kvArr->arr = NULL;
  kvArr->length = 0;
  int count = 0;

  while(getline(&line, &sz, f ) >= 0){
    kvArr->arr = realloc(kvArr->arr, (count + 1) * sizeof(*kvArr->arr));
    
    kvArr->arr[count] = findPair(line);
    count++;
    free(line);
    line = NULL;
  }
  kvArr->length = count;
  free(line);
  
   if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        exit(EXIT_FAILURE);
      }

  return kvArr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i = 0; i < pairs->length; i++){
    free(pairs->arr[i]->key);
    free(pairs->arr[i]->value);
    free(pairs->arr[i]);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i = 0; i < pairs->length; i++){
    printf("key = '%s' value = '%s'\n", pairs->arr[i]->key, pairs->arr[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(int i = 0; i < pairs->length; i++){
    if(strcmp(pairs->arr[i]->key, key) == 0){
      return pairs->arr[i]->value;
    }
  }
  return NULL;
}
