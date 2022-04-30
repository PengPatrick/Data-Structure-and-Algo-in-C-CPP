#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

void stripNewLine1(char * str){
  char * p = strchr(str, '\n');
  if(p != NULL){
    *p = '\0';
  }

}



counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE *f = fopen(filename, "r");
  if (f == NULL){
    fprintf(stderr,"count not find the file ");
    exit( EXIT_FAILURE);
     
  }
  char * line = NULL;
  size_t  sz = 0;
  
  counts_t*  myCount = createCounts();
  while(getline(&line, &sz,f) >= 0){
    stripNewLine1(line);
    char * value = lookupValue(kvPairs, line);
    addCount(myCount, value);

   }
   free(line);

   if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        exit( EXIT_FAILURE);
      }
   
  return myCount;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if(argc < 3){
    perror("error");
    exit(EXIT_FAILURE);
  }

   kvarray_t * kv = readKVs(argv[1]);


   
  
 //count from 2 to argc (call the number you count i)

   
   for(int i = 0; i < argc; i++){
     counts_t*  c =  countFile(argv[i], kv);
     char * outName =  computeOutputFileName(argv[i]);
     

   

     FILE *f = fopen(outName, "w");
    if (f == NULL){
      fprintf(stderr,"count not find the file ");
      return EXIT_FAILURE;
     
    }

    printCounts(c, f);
     if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)


    //open the file named by outName (call that f)

    //print the counts from c into the FILE f

    //close f

    //free the memory for outName and c
     free(outName);
     freeCounts(c);

   }
 //free the memory for kv
   freeKVs(kv);

  return EXIT_SUCCESS;
}


