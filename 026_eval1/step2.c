//This file is for Step 2.
//You should do 
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sum_seq2
//  Step 2 (D): add test cases to main to test sum_seq2
// 
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq2(int x){
  // Step 2A
  return -2 + (x - 2)*(x - 2);
}

int sum_seq2(int low, int high){
  // Step 2C
  if(low < high){
    int sum = 0;
    for(int i = low; i < high; i++){
      sum += seq2(i);
    }
    return sum;
  }else{
    return 0;
  }
}


int main(void){
  // Step 2B
  for(int i = -6; i < 15; i++){
    printf("seq2(%d) = %d\n", i, seq2(i));
  }
  //printf("seq2(%d) = %d\n", 0, seq2(0));
  //printf("seq2(%d) = %d\n", 2, seq2(2));
  //printf("seq2(%d) = %d\n", -3, seq2(-3));
  //printf("seq2(%d) = %d\n", 12, seq2(12));
  printf("seq2(%d) = %d\n", -8, seq2(-8));
  //printf("seq2(%d) = %d\n", 13, seq2(13));

  // Step 2D
  for(int i = -4; i <= 14; i++){
    printf("sum_seq2(%d, %d) = %d\n", i, 14, sum_seq2(i, 14));
  }
  printf("sum_seq2(%d, %d) = %d\n", 0, 2, sum_seq2(0, 2));
  printf("sum_seq2(%d, %d) = %d\n", 1, 7, sum_seq2(1, 7));
  printf("sum_seq2(%d, %d) = %d\n", -3, 12, sum_seq2(-3, 12));
  printf("sum_seq2(%d, %d) = %d\n", -8, 8, sum_seq2(-8, 8));
  printf("sum_seq2(%d, %d) = %d\n", 0, 0, sum_seq2(0, 0));
  printf("sum_seq2(%d, %d) = %d\n", 9, 7, sum_seq2(9, 7));
  return 0;
}

