#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "assert.h"
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};
class linearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg - 10; }
};
//class squareFunction : public Function<int, int> {
//};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int num;
  if (high > low) {
    num = log(high - low) / log(2) + 1;
  }
  else {
    num = 1;
  }
  CountedIntFn * func = new CountedIntFn(num, f, mesg);
  int n = binarySearchForZero(func, low, high);
  assert(n == expected_ans);
}

int main() {
  Function<int, int> * fsin = new SinFunction();

  check(fsin, 0, 150000, 52359, "check sin");
  check(fsin, 52359, 150000, 52359, "check sin");
  check(fsin, 0, 52359, 52358, "check sin");

  Function<int, int> * fl = new linearFunction();
  check(fl, -99999999, 150000, 10, "check linear");
  return EXIT_SUCCESS;
}
