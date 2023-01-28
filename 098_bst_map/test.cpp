#include <iostream>

#include "bstmap.h"
int main(void) {
  BstMap<int, int> map;
  map.add(1, 11);
  map.add(2, 10);
  map.add(44, 9);
  std::cout << map;
  map.remove(2);
  std::cout << map;
  map.remove(44);
  std::cout << map;
  return EXIT_SUCCESS;
}
