#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <vector>

class Page {
 private:
  // Property for Page
  size_t pageNum;
  std::string pageType;
  std::vector<std::string> text;
  std::vector<std::string> choices;
  std::vector<size_t> dest;
  std::vector<size_t> isDestValid;

 public:
  Page();
  // Initialize Page with three parameters, for pageNum, pageType and text
  Page(size_t num, std::string type, std::string pagefile);
  // Print the current page, for step1, as there are some special requirements
  void printPage();
  // Print the page content, for step2 - 4
  // void printPageContent(std::vector<std::pair<std::string, size_t> > & extra);
  void printPageContent();
  // Print the text of the page
  void printText();
  // Print the choices of the page, for step1
  void printChoice();
  // Update according to variable map for choice, for step4 special variable
  void updateValid(std::vector<std::pair<std::string, size_t> > & extra);
  // Print the choices of the page for step4 special variable
  //void printChoice(std::vector<std::pair<std::string, size_t> > & extra);
  // According to choice string, parse it into several choices
  void setChoices(std::string choice);
  // Set dest page for N page
  void setDest(size_t pageNum);
  // Get the current Page type
  std::string getPageType() const;
  // Get the current choice size (how many slices)
  size_t getChoiceSize() const;
  // Get the Dest pageNum
  size_t getDest(size_t index) const;
  // Check if the Dest is valid, for step4, if invalid, should print <UNAVAILABLE>
  size_t isValidDest(size_t index) const;
};
