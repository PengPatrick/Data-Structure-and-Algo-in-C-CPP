#include "story.hpp"

#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

Story::Story() {
}

Story::Story(std::string filename) {
  std::string storyPath = filename + "/" + "story.txt";
  std::ifstream ifStory(storyPath.c_str());
  std::string str;

  if (!ifStory.is_open()) {
    std::cerr << "Cannot open the file!" << std::endl;
    exit(EXIT_FAILURE);
  }
  while (std::getline(ifStory, str)) {
    if (str.empty()) {
      continue;
    }
    // Check the input and category it into type 0-4
    size_t type = checkStrType(str);

    size_t colonPos = str.find(':');
    size_t atPos = str.find('@');
    size_t brtLPos = str.find('[');
    size_t dollarPos = str.find('$');
    size_t equalPos = str.find('=');

    // Invalid category
    if (type == 0) {
      std::cerr << "Wrong format of input, please check!" << std::endl;
      exit(EXIT_FAILURE);
    }
    // Type 1: pageNum@type:filename
    if (type == 1) {
      std::string pageNumStr = str.substr(0, atPos);
      size_t pageNum = std::strtoull(pageNumStr.c_str(), NULL, 10);
      if (pageNum != storySeries.size()) {
        std::cerr << "Wrong sequence of initialize page!" << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string pageType = str.substr(atPos + 1, 1);
      std::string pagePath = filename + "/" + str.substr(colonPos + 1);
      storySeries.push_back(Page(pageNum, pageType, pagePath));
    }
    // Type 2: pageNum:destpage:text
    if (type == 2) {
      std::string pageNumStr = str.substr(0, colonPos);
      size_t pageNum = std::strtoull(pageNumStr.c_str(), NULL, 10);
      if (pageNum > storySeries.size() - 1) {
        std::cerr << "No such pages, please initialize it before use it!" << std::endl;
        exit(EXIT_FAILURE);
      }
      if (storySeries[pageNum].getPageType().compare("N") != 0) {
        std::cerr << "Win and Lose page cannot have choices" << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string left = str.substr(colonPos + 1);
      storySeries[pageNum].setChoices(left);
    }
    // Type 4: pageNum[var=value]:dest:text
    if (type == 4) {
      std::string pageNumStr = str.substr(0, brtLPos);
      size_t pageNum = std::strtoull(pageNumStr.c_str(), NULL, 10);
      if (pageNum > storySeries.size() - 1) {
        std::cerr << "No such pages, please initialize it before use it!" << std::endl;
        exit(EXIT_FAILURE);
      }
      storySeries[pageNum].setChoices(str.substr(brtLPos));
    }
    // Type 3: pageNum$var=value
    if (type == 3) {
      std::string pageNumStr = str.substr(0, dollarPos);
      size_t pageNum = std::strtoull(pageNumStr.c_str(), NULL, 10);
      if (pageNum > storySeries.size() - 1) {
        std::cerr << "No such pages, please initialize it before use it!" << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string type = str.substr(dollarPos + 1, equalPos - dollarPos - 1);
      std::string typeNumStr = str.substr(equalPos + 1);
      size_t typeNum = std::strtoull(typeNumStr.c_str(), NULL, 10);
      std::map<size_t, std::vector<std::pair<std::string, size_t> > >::iterator it =
          extra_choice.find(pageNum);
      if (it != extra_choice.end()) {
        it->second.push_back(std::make_pair(type, typeNum));
      }
      std::vector<std::pair<std::string, size_t> > extra_pairs;
      extra_pairs.push_back(std::make_pair(type, typeNum));
      extra_choice.insert(std::make_pair(pageNum, extra_pairs));
    }
  }
  ifStory.close();
}

size_t Story::isValidNumber(std::string str) {
  char * str_end;
  size_t number = std::strtoull(str.c_str(), &str_end, 10);
  if (number >= 0 && *str_end == '\0') {
    return 1;
  }
  return 0;
}

size_t Story::isValidType(std::string str) {
  if (str.compare("W") == 0 || str.compare("L") == 0 || str.compare("N") == 0) {
    return 1;
  }
  return 0;
}

size_t Story::checkStrType(std::string str) {
  size_t dollarPos = str.find('$');
  size_t atPos = str.find('@');
  size_t brtLPos = str.find('[');
  size_t brtRPos = str.find(']');
  size_t equalPos = str.find('=');
  size_t colonPos = str.find(':');

  // Check the type 1: pageNum@destType:filename
  if (atPos > 0 && atPos < brtLPos && atPos < dollarPos && atPos < colonPos) {
    // @ exsist and earlier than '[','$',':', more check on pageNum@destType:filename
    if (colonPos != std::string::npos && str.find(".txt") != std::string::npos) {
      std::string pageNum = str.substr(0, atPos);
      std::string destType = str.substr(atPos + 1, colonPos - atPos - 1);
      if (isValidNumber(pageNum) && isValidType(destType)) {
        return 1;
      }
    }
  }
  // Check the type 2: pageNum:destPage:text
  if (colonPos > 0 && colonPos < brtLPos && colonPos < dollarPos && colonPos < atPos) {
    // : exsist and earlier than '[','$','@', more check on pageNum:destPage:text
    std::string pageNum = str.substr(0, colonPos);
    std::string left = str.substr(colonPos + 1);
    size_t colonPos2 = left.find(':');
    if (colonPos2 != std::string::npos) {
      std::string destPage = left.substr(0, colonPos2);
      if (isValidNumber(pageNum) && isValidNumber(destPage)) {
        return 2;
      }
    }
  }
  // Check the type 3: pageNum$var=value
  if (dollarPos > 0 && dollarPos < atPos && dollarPos < brtLPos && dollarPos < colonPos) {
    // $ exsist and earlier than '@','[',':', more check on pageNum$var=value
    if (equalPos != std::string::npos) {
      std::string pageNum = str.substr(0, dollarPos);
      std::string value = str.substr(equalPos + 1);
      if (isValidNumber(pageNum) && isValidNumber(value)) {
        return 3;
      }
    }
  }
  // Check the type 4: pageNum[var=value]:dest:text
  if (brtLPos > 0 && brtLPos < atPos && brtLPos < dollarPos && brtLPos < colonPos &&
      brtLPos < brtRPos) {
    // $ exsist and earlier than '@','[',':',']', more check on pageNum$var=value
    if (equalPos != std::string::npos && brtRPos - brtLPos > 2) {
      std::string pageNum = str.substr(0, brtLPos);
      std::string value = str.substr(equalPos + 1, brtRPos - equalPos - 1);
      std::string left = str.substr(colonPos + 1);
      size_t colonPos2 = left.find(':');
      if (colonPos2 != std::string::npos) {
        std::string dest = left.substr(0, colonPos2);
        if (isValidNumber(pageNum) && isValidNumber(value) && isValidNumber(dest)) {
          return 4;
        }
      }
    }
  }
  // All other type with return value = 0
  return 0;
}

void Story::checkStory() {
  size_t storySize = getStorySize();
  // Check if referenced
  std::vector<size_t> referenced(storySize, 0);
  referenced[0] = 1;
  // Count win and lose, should larger or equal than 1
  size_t countWin = 0;
  size_t countLose = 0;
  for (size_t i = 0; i < storySize; i++) {
    if (storySeries[i].getPageType().compare("W") == 0) {
      countWin++;
    }
    else if (storySeries[i].getPageType().compare("L") == 0) {
      countLose++;
    }
    else {
      size_t choiceSize = storySeries[i].getChoiceSize();
      for (size_t j = 0; j < choiceSize; j++) {
        size_t destNum = storySeries[i].getDest(j + 1);
        if (destNum > storySize - 1) {
          std::cerr << "Cannot reach a page which doesn't exsist!" << std::endl;
          exit(EXIT_FAILURE);
        }
        referenced[destNum] = 1;
      }
    }
  }
  if (countWin == 0 || countLose == 0) {
    std::cerr << "There should be at least one win/lose page!" << std::endl;
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < storySize; i++) {
    if (referenced[i] == 0) {
      std::cerr << "Every page should be referenced!" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

void Story::printStory() {
  std::vector<Page>::iterator it = storySeries.begin();

  while (it != storySeries.end()) {
    it->printPage();
    ++it;
  }
}

void Story::readStory() {
  std::string str;
  size_t curPageNum = 0;
  std::vector<std::pair<std::string, size_t> > extraVal;
  size_t isPrint = 0;
  // read from standard input
  while (std::getline(std::cin, str)) {
    if (!isValidNumber(str)) {
      std::cerr << "Wrong input format!" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::map<size_t, std::vector<std::pair<std::string, size_t> > >::iterator it =
        extra_choice.begin();
    while (it != extra_choice.end()) {
      if (it->first == curPageNum) {
        std::vector<std::pair<std::string, size_t> >::iterator it1 = it->second.begin();
        while (it1 != it->second.end()) {
          extraVal.push_back(*it1);
          ++it1;
        }
      }
      ++it;
    }
    storySeries[curPageNum].updateValid(extraVal);
    if (isPrint == 0) {
      //storySeries[curPageNum].printPageContent(extraVal);
      storySeries[curPageNum].printPageContent();
      isPrint = 1;
    }
    if (str.empty()) {
      continue;
    }
    size_t choiceNum = std::strtoull(str.c_str(), NULL, 10);
    if (storySeries[curPageNum].getPageType().compare("W") == 0 ||
        storySeries[curPageNum].getPageType().compare("L") == 0) {
      break;
    }
    else if (choiceNum <= 0 || choiceNum > storySeries[curPageNum].getChoiceSize()) {
      std::cout << "That is not a valid choice, please try again" << '\n';
      continue;
    }
    size_t destPageNum = storySeries[curPageNum].getDest(choiceNum);
    if (storySeries[curPageNum].isValidDest(choiceNum) == 0) {
      std::cout << "That choice is not available at this time, please try again" << '\n';
      continue;
    }
    curPageNum = destPageNum;
    isPrint = 0;
  }
}

size_t Story::getStorySize() {
  return storySeries.size();
}

void Story::printWin() {
  std::vector<std::vector<std::pair<size_t, size_t> > > winPath;
  std::vector<std::pair<size_t, size_t> > oneWinPath;
  size_t size = getStorySize();

  std::vector<int> visited(size, 0);
  getWinPath(winPath, oneWinPath, 0, visited);
  if (winPath.size() == 0) {
    std::cout << "This story is unwinnable!" << '\n';
    return;
  }
  // print all path
  std::vector<std::vector<std::pair<size_t, size_t> > >::iterator it = winPath.begin();
  while (it != winPath.end()) {
    std::vector<std::pair<size_t, size_t> >::iterator it1 = it->begin();
    while (it1 != it->end()) {
      if (it1->second != 0) {
        std::cout << it1->first << "(" << it1->second << ")"
                  << ",";
        ++it1;
      }
      else {
        std::cout << it1->first << "(win)" << '\n';
        ++it1;
      }
    }
    ++it;
  }
}

void Story::getWinPath(std::vector<std::vector<std::pair<size_t, size_t> > > & winPath,
                       std::vector<std::pair<size_t, size_t> > & oneWinPath,
                       size_t pageNum,
                       std::vector<int> & visited) {
  // If find win, add
  if (storySeries[pageNum].getPageType().compare("W") == 0) {
    oneWinPath.push_back(std::make_pair(pageNum, 0));
    winPath.push_back(oneWinPath);
    oneWinPath.pop_back();
    return;
  }
  // if lose or visited, do nothing
  if (storySeries[pageNum].getPageType().compare("L") == 0 || visited[pageNum] == 1) {
    return;
  }
  // mark
  visited[pageNum] = 1;
  oneWinPath.push_back(std::make_pair(pageNum, 1));
  for (size_t i = 0; i < storySeries[pageNum].getChoiceSize(); i++) {
    oneWinPath.pop_back();
    oneWinPath.push_back(std::make_pair(pageNum, i + 1));
    getWinPath(winPath, oneWinPath, storySeries[pageNum].getDest(i + 1), visited);
  }
  oneWinPath.pop_back();
  visited[pageNum] = 0;
}
