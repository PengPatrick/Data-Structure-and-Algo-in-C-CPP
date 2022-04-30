//This file is for Step 3.
//You should do 
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write count_neg_seq3_range
//  Step 3 (D): add test cases to main to test count_neg_seq3_range
// 
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y){
  // Step 3A
  return 3 + (x - 1)*(y + 4);
}

int count_neg_seq3_range(int xLow, int xHi, int yLow, int yHi){
  // Step 3C
  if(xLow < xHi && yLow < yHi){
    int count = 0;
    for(int X = xLow; X < xHi; X++){
      for(int Y = yLow; Y < yHi; Y++){
        if(seq3(X, Y) < 0){
          count += 1;
        }
      }
    }
    return count;
  }else{
    return 0;
  }
}

int main(void){
  // Step 3B
  
  printf("seq3(%d, %d) = %d\n", -4, -5, seq3(-4, -5));
  printf("seq3(%d, %d) = %d\n", 0, 0, seq3(0, 0));
  printf("seq3(%d, %d) = %d\n", 1, 4, seq3(1, 4));
  printf("seq3(%d, %d) = %d\n", 3, -4, seq3(3, -4));
  printf("seq3(%d, %d) = %d\n", 1, 5, seq3(1, 5));
  printf("seq3(%d, %d) = %d\n", -8, -5, seq3(-8, -5));
  printf("seq3(%d, %d) = %d\n", -4, 7, seq3(-4, 7));
  printf("seq3(%d, %d) = %d\n", 6, 6, seq3(6, 6));
  printf("seq3(%d, %d) = %d\n", -6, -6, seq3(-6, -6));

  // Step 3D
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, count_neg_seq3_range(0, 2, 0, 3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -1, 1, -1, 1, count_neg_seq3_range(-1, 1, -1, 1));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -1, 4, -1, 3, count_neg_seq3_range(-1, 4, -1, 3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -5, 6, -5, 6, count_neg_seq3_range(-5, 6, -5, 6));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -6, 1, -1, 6, count_neg_seq3_range(-6, 1, -1, 6));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -6, 7, -6, 7, count_neg_seq3_range(-6, 7, -6, 7));
  
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -1, -1, -1, 1, count_neg_seq3_range(-1, -1, -1, 1));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -1, 1, -1, -1, count_neg_seq3_range(-1, 1, -1, -1));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -1, -1, -1, -1, count_neg_seq3_range(-1, -1, -1, -1));

  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", 2, 0, -1, 0, count_neg_seq3_range(2, 0, -1, 0));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", -1, 0, 2, 0, count_neg_seq3_range(-1, 0, 2, 0));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n", 2, 0, 2, 0, count_neg_seq3_range(2, 0, 2, 0));
  return 0;
}
