#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printFile(FILE *f){
  size_t count = 0;
  char *line = NULL;
  char ** arr = NULL;
  size_t sz = 0;

  while(getline(&line, &sz, f) >= 0){
    count++;
    arr = realloc(arr, count*sizeof(*arr));
    arr[count - 1] = line;
    line = NULL;
  }
  free(line);

  sortData(arr,count);

  for(size_t i = 0; i < count; i++){
    printf("%s", arr[i]);
    free(arr[i]);
  }
  free(arr);
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  if(argc == 1){
    FILE *f = stdin;
    if(f == NULL){
      fprintf(stderr, "No file found!");
      return EXIT_FAILURE;
    }
    printFile(f);
  }else{
    for(int i = 1; i < argc; i++){
      FILE *f = fopen(argv[i], "r");
      if(f == NULL){
	fprintf(stderr, "No file found!");
	return EXIT_FAILURE;
      }
      printFile(f);
      if(fclose(f) != 0){
	perror("Fail to close the file!");
	return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
