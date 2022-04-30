//This file is for Step 1.
//You should do 
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write print_seq1_range
//  Step 1 (D): add test cases to main to test print_seq1_range
// 
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x){
  return 3*x-5;
}


void print_seq1_range(int low, int high){
  if(low < high){
    for(int i = low; i < high; i++){
      printf("%d", seq1(i));
      printf(", ");
    }
    printf("%d\n", seq1(high));
  }else{
    printf("\n");
  }
}


int main(void){
  for(int i = -6; i < 10; i++){
    printf("seq1(%d) = %d\n", i, seq1(i));
  }
  //printf("seq1(%d) = %d\n", 3, seq1(3));
  //printf("seq1(%d) = %d\n", 0, seq1(0));
  //printf("seq1(%d) = %d\n", 7, seq1(7));
  //printf("seq1(%d) = %d\n", -5, seq1(-5));
  //printf("seq1(%d) = %d\n", -3, seq1(-3));
  //printf("seq1(%d) = %d\n", 9, seq1(9));

  printf("print_seq1_range(%d, %d)\n", -3, 7);
  print_seq1_range(-3, 7);
  printf("print_seq1_range(%d, %d)\n", -5, 7);
  print_seq1_range(-5, 7);
  printf("print_seq1_range(%d, %d)\n", -3, 9);
  print_seq1_range(-3, 9);
  printf("print_seq1_range(%d, %d)\n", -5, 9);
  print_seq1_range(-5, 9);
  printf("print_seq1_range(%d, %d)\n", 0, 0);
  print_seq1_range(0, 0);
  printf("print_seq1_range(%d, %d)\n", -3, -3);
  print_seq1_range(-3, -3);
  printf("print_seq1_range(%d, %d)\n", 5, 0);
  print_seq1_range(5, 0);
  return 0;
}


