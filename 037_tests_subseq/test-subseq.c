

#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test(int * array, size_t n, size_t expected_ans){
  if(maxSeq(array, n) != expected_ans){
    printf("Unexpected Anwser!");
    exit(EXIT_FAILURE);
  }
}

int main(void){
  int arr1[5] = {1, 2, 3, 4, 5};
  int arr2[4] = {1, 2, 1, 4};
  int arr3[0];
  int arr4[4] = {2, 2, 2, 2};
  int arr5[5] = {5, 4, 3, 2, 1};
  int arr6[5] = {-1, 0, -2, -1, 0};
  int arr7[4] = {1, 100, 1000, 10000};
  int arr8[1] = {0};
  int arr9[4] = {1, 1, 2, 2};
  int arr10[7] = {20, 10, 1, 3, 5, 10, 5};
  int arr11[8] = {1, 2, 3, 4, -1, 5, 6, 7};

  test(arr1, 5, 5);
  test(arr2, 4, 2);
  test(arr3, 0, 0);
  test(arr4, 4, 1);
  test(arr5, 5, 1);
  test(arr6, 5, 3);
  test(arr7, 4, 4);
  test(arr8, 1, 1);
  test(arr9, 4, 2);
  test(arr10, 7, 4);
  test(arr11, 8, 4);
  return EXIT_SUCCESS;
}
