unsigned power(unsigned x, unsigned y){
  // include the case : x = 0, y = 0
  if(y == 0){
    return 1;
  }
  return x * power(x, y-1);
}
