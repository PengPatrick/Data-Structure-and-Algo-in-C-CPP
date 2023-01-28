#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "page.hpp"

class Story {
 private:
  std::vector<Page> storySeries;
  std::map<size_t, std::vector<std::pair<std::string, size_t> > > extra_choice;

 public:
  Story();
  Story(std::string filename);
  size_t isValidNumber(std::string str);
  size_t isValidType(std::string str);
  size_t checkStrType(std::string str);
  void checkStory();
  void printStory();
  void readStory();
  size_t getStorySize();
  void printWin();
  void getWinPath(std::vector<std::vector<std::pair<size_t, size_t> > > & winPath,
                  std::vector<std::pair<size_t, size_t> > & oneWinPath,
                  size_t choiceNum,
                  std::vector<int> & visited);
};
