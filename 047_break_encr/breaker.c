#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int freqIndex(FILE *f){
  int c;
  int freq[26] = {0};
  while((c = fgetc(f)) != EOF){
      if(isalpha(c)){
	freq[c - 'a']++;
      }
  }

  int index = 0;
  int max = 0;
  for(int i = 0; i < 26; i++){
    if(freq[i] > max){
      index = i;
      max = freq[i];
    }
  }
  return index;
}

int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "Incorrect Number of Command Line Arguments!");
    return EXIT_FAILURE;
  }

  FILE *f = fopen(argv[1], "r");
  if(f == NULL){
    fprintf(stderr, "Fail to Open the File!");
    return EXIT_FAILURE;
  }

  int key = (freqIndex(f) + 'a' -'e' + 26) % 26;

  if(key >= 0 && key < 26){
    fprintf(stdout, "%d\n", key);
  }else{
    fprintf(stderr, "Cannot Encrypt!");
  }

  if(fclose(f) != 0){
    perror("Failed to Close the File");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS; 
}
