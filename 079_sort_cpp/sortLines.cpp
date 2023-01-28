#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

void printVec(std::vector<std::string> vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << std::endl;
  }
}

int main(int argc, char ** argv) {
  std::vector<std::string> vec;
  std::string str;
  std::ifstream file;
  if (argc == 1) {
    while (!std::cin.eof()) {
      std::getline(std::cin, str);
      vec.push_back(str);
      std::sort(vec.begin(), vec.end());
      printVec(vec);
      vec.clear();
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      file.open(argv[i]);
      if (file.fail()) {
        std::cerr << "fail to open file" << std::endl;
        exit(EXIT_FAILURE);
      }
      while (!file.eof()) {
        std::getline(file, str);
        vec.push_back(str);
      }
      file.close();
      std::sort(vec.begin(), vec.end());
      printVec(vec);
      vec.clear();
    }
  }

  return 0;
}
