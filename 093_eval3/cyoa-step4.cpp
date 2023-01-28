#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong number of command line arguments!" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string filename = argv[1];
  Story p(argv[1]);
  p.checkStory();
  p.readStory();
  return EXIT_SUCCESS;
}
