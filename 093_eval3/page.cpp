#include "page.hpp"

#include <iostream>
#include <sstream>

Page::Page() : pageNum(0), pageType(NULL) {
}
Page::Page(size_t num, std::string type, std::string pagefile) :
    pageNum(num), pageType(type) {
  // Parse the pagefile path and open the file
  std::string pagePath = pagefile;
  std::ifstream ifPage(pagePath.c_str());
  std::string str;
  if (!ifPage.is_open()) {
    std::cerr << "Cannot open the file!" << std::endl;
    exit(EXIT_FAILURE);
  }
  // store the text
  while (std::getline(ifPage, str)) {
    text.push_back(str);
  }
}
void Page::printPage() {
  // Special print for step1
  std::cout << "Page " << pageNum << '\n';
  std::cout << "==========" << '\n';
  printText();
  std::cout << '\n';
  if (pageType.compare("W") == 0) {
    std::cout << "Congratulations! You have won. Hooray!" << '\n';
  }
  else if (pageType.compare("L") == 0) {
    std::cout << "Sorry, you have lost. Better luck next time!" << '\n';
  }
  else {
    printChoice();
  }
}
/*
void Page::printPageContent() {
  printText();
  std::cout << '\n';
  if (pageType.compare("W") == 0) {
    std::cout << "Congratulations! You have won. Hooray!" << '\n';
  }
  else if (pageType.compare("L") == 0) {
    std::cout << "Sorry, you have lost. Better luck next time!" << '\n';
  }
  else {
    printChoice();
  }
}
*/

void Page::
    printPageContent() {  //(std::vector<std::pair<std::string, size_t> > & extra) {
  // Print format for step2-4
  printText();
  std::cout << '\n';
  // If it is win page
  if (pageType.compare("W") == 0) {
    std::cout << "Congratulations! You have won. Hooray!" << '\n';
  }
  // If it is lose page
  else if (pageType.compare("L") == 0) {
    std::cout << "Sorry, you have lost. Better luck next time!" << '\n';
  }
  else {
    // Only for N page
    //printChoice(extra);
    printChoice();
  }
}

void Page::printText() {
  // print all string from text
  std::vector<std::string>::iterator it = text.begin();
  while (it != text.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}
/*
void Page::printChoice() {
  // For step1
  std::cout << "What would you like to do?" << '\n';
  std::cout << '\n';

  std::vector<std::string>::iterator it = choices.begin();
  while (it != choices.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}
*/
void Page::updateValid(std::vector<std::pair<std::string, size_t> > & extra) {
  // According to choice type to define choice is valid or not
  std::vector<std::string>::iterator it = choices.begin();
  while (it != choices.end()) {
    // If the types belong to type 1 and type 2 (step1 - step3), valid
    if (it->find('[') == std::string::npos) {
      isDestValid.push_back(1);
    }
    else {
      // According to updated map to define whether it is valid
      std::string::size_type bStartPos = it->find('[');
      std::string::size_type equalPos = it->find('=');
      std::string::size_type bEndPos = it->find(']');
      std::string type = it->substr(bStartPos + 1, equalPos - bStartPos - 1);
      std::string typeNumStr = it->substr(equalPos + 1, bEndPos);
      size_t typeNum = std::strtoull(typeNumStr.c_str(), NULL, 10);
      std::vector<std::pair<std::string, size_t> >::iterator it1 = extra.begin();
      size_t valid = 0;
      size_t exsist = 0;
      // Iterate over to find in the map. If match then it is valid
      while (it1 != extra.end()) {
        if (it1->first.compare(type) == 0) {
          if (it1->second == typeNum) {
            valid = 1;
            isDestValid.push_back(valid);
            break;
          }
          exsist = 1;
        }
        ++it1;
      }
      // If cannot find matching category, treat as value = 0
      if (exsist == 0) {
        if (typeNum == 0) {
          valid = 1;
          isDestValid.push_back(valid);
        }
      }
      if (valid == 0) {
        isDestValid.push_back(valid);
      }
    }
    ++it;
  }
}

void Page::printChoice() {  //std::vector<std::pair<std::string, size_t> > & extra) {
  std::cout << "What would you like to do?" << '\n';
  std::cout << '\n';
  std::vector<std::string>::iterator it = choices.begin();
  size_t index = 1;
  while (it != choices.end()) {
    if (it->find('[') == std::string::npos) {
      std::cout << *it << std::endl;
    }
    else {
      // for step4
      std::string::size_type bStartPos = it->find('[');
      if (isDestValid[index - 1] == 1) {
        std::string choice = it->substr(0, bStartPos);
        std::cout << choice << '\n';
      }
      else {
        // invalid choice
        std::string::size_type dotPos = it->find('.');
        std::string choiceNum = it->substr(0, dotPos + 1);
        std::cout << choiceNum << " <UNAVAILABLE>" << '\n';
      }
    }
    ++it;
    ++index;
  }
}
void Page::setChoices(std::string choice) {
  size_t index = choices.size();
  // If standard format
  if (choice.find('[') == std::string::npos) {
    std::string::size_type pos = choice.find(':');
    std::string destNumStr = choice.substr(0, pos);
    size_t destNum = std::strtoull(destNumStr.c_str(), NULL, 10);
    dest.push_back(destNum);

    std::stringstream ss;
    ss << " ";
    ss << index + 1;
    ss << ". ";
    ss << choice.substr(pos + 1);
    choices.push_back(ss.str());
  }
  else {
    // If step4 specail case
    std::string::size_type firstColon = choice.find(':');
    std::string extra_str = choice.substr(0, firstColon);
    std::string left = choice.substr(firstColon + 1);
    std::string::size_type pos = left.find(':');
    std::string destNumStr = left.substr(0, pos);
    size_t destNum = std::strtoull(destNumStr.c_str(), NULL, 10);
    dest.push_back(destNum);
    std::stringstream ss;
    ss << " ";
    ss << index + 1;
    ss << ". ";
    ss << left.substr(pos + 1);
    ss << extra_str;
    choices.push_back(ss.str());
  }
}

void Page::setDest(size_t pageNum) {
  dest.push_back(pageNum);
}

std::string Page::getPageType() const {
  return pageType;
}

size_t Page::getChoiceSize() const {
  return choices.size();
}

size_t Page::getDest(size_t index) const {
  return dest[index - 1];
}

size_t Page::isValidDest(size_t index) const {
  return isDestValid[index - 1];
}
