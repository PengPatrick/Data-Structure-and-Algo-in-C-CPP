#include <stdio.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t count = 1;
  size_t max = 1;

  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      count++;
      max = (max >= count ? max : count);
    }
    else {
      count = 1;
    }
  }
  return max;
}
