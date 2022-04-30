#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans){
  if(power(x, y) != expected_ans){
    printf("Unexpected answer!");
    exit(EXIT_FAILURE);
  }
}

int main(){
  run_check(0, 0, 1);
  run_check(0, 2, 0);
  run_check(3, 0, 1);
  run_check(1, 1, 1);
  run_check(2, 1, 2);
  run_check(1, 3, 1);
  run_check(-2, 3, -8);
  run_check(-2, 2, 4);
  run_check(2, 20, 1048576);
  run_check(3, 4, 81);

  return EXIT_SUCCESS;
}
