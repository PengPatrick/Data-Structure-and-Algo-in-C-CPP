#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low < high - 1) {
    int mid = low + (high - low) / 2;
    int pix = f->invoke(mid);
    if (pix == 0) {
      return mid;
    }
    else if (pix > 0) {
      high = mid;
    }
    else {
      low = mid;
    }
  }
  return low;
}
