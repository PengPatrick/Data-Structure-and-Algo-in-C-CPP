
#include "pandemic.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check if comma delimiter exists and only appears once
void checkComma(const char * line) {
  int countComma = 0;
  for (size_t i = 0; line[i] != '\0'; i++) {
    if (line[i] == ',') {
      countComma++;
    }
  }
  if (countComma != 1) {
    fprintf(stderr, "Wrong format of input, wrong number of comma delimiter!\n");
    exit(EXIT_FAILURE);
  }
}

// Check if country name is legal
void checkCountryName(const char * line) {
  char * commaDel = strchr(line, ',');

  // Check if there is any country name
  //if (commaDel - line == 0) {
  //  fprintf(stderr, "Wrong format of input, no country name!");
  //  exit(EXIT_FAILURE);
  //}

  // Check if country name <= 63, reserve a place for '\0'
  if (commaDel - line > MAX_NAME_LEN - 1) {
    fprintf(stderr, "Wrong format of input, country name is too long!\n");
    exit(EXIT_FAILURE);
  }
}

/*
void parseCountryName(const char * line, char str[64]) {
  size_t i = 0;
  for (; line[i] != '\0'; i++) {
    str[i] = line[i];
  }
  str[i] = '\0';
}
*/

int isNumber(char ch) {
  if (ch < '0' || ch > '9') {
    return 0;
  }
  return 1;
}

// Check if population is legal
void checkPopulation(const char * line) {
  char * popStart = strchr(line, ',') + 1;
  // Check if population is empty
  if (*popStart == '\n') {
    fprintf(stderr, "Wrong format of input, no population number!\n");
    exit(EXIT_FAILURE);
  }
  // Check if begins with space, if so, ignore
  if (*popStart == ' ') {
    while (*popStart == ' ') {
      popStart++;
    }
  }
  //long firstCh = popStart - line;
  while (*popStart != '\n') {
    /*
    // Check if the population is in format of 012345, which is not allowed
    if (*(popStart + 1) != '\n' && popStart - line == firstCh && *popStart == '0') {
      fprintf(stderr, "Wrong format of input, population number start with 0!");
      exit(EXIT_FAILURE);
    }
    */
    if (!isNumber(*popStart)) {
      if (*popStart == '+' && isNumber(*(popStart + 1))) {
      }
      else {
        fprintf(stderr, "Wrong format of input, wrong format of population number!\n");
        exit(EXIT_FAILURE);
      }
    }
    popStart++;
  }
}

// Parse the population
uint64_t parsePopulation(const char * line) {
  char * popStart = strchr(line, ',') + 1;
  char * popEnd;
  // uint64 == unsigned long long
  unsigned long long popNum = strtoull(popStart, &popEnd, 10);
  // Check if the number exceeds the upper bound
  if (popNum == ULLONG_MAX && errno == ERANGE) {
    fprintf(stderr, "Wrong format of input, population exceed the largest number!\n");
    exit(EXIT_FAILURE);
  }
  return popNum;
}

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  // check the line read
  if (line == NULL) {
    fprintf(stderr, "No line is read!\n");
    exit(EXIT_FAILURE);
  }
  // Check the input line format: comma number, countryname, population
  checkComma(line);
  checkCountryName(line);
  checkPopulation(line);

  // Parse the countryName
  size_t i = 0;
  for (; line[i] != ','; i++) {
    ans.name[i] = line[i];
  }
  ans.name[i] = '\0';

  // parseCountryName(line, ans.name);
  // Parse the population, in unint_64 format
  ans.population = parsePopulation(line);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  // check the input data
  if (data == NULL) {
    fprintf(stderr, "No data!\n");
    exit(EXIT_FAILURE);
  }
  // provides the solution of n_days < 7, so it is not an error case, do nothing
  if (n_days < 7) {
    //perror("Less than seven days for average!");
    //exit(EXIT_FAILURE);
    return;
  }
  double sum = 0;
  /*
  for(size_t i = 0; i < n_days - 6; i++){
    double sum = 0;
    for(size_t j = 0; j < 7; j++){
      sum += data[j];
    }
    avg[i] = sum / 7;
  }
  */
  for (size_t i = 0; i < 7; i++) {
    sum += data[i];
  }
  avg[0] = sum / 7;
  // Sliding window, pay attention to the length!
  for (size_t i = 1; i < n_days - 6; i++) {
    sum = sum - data[i - 1] + data[i + 6];
    avg[i] = sum / 7.0;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  // what about population is 0? error or nan.
  // Check the input data
  if (data == NULL) {
    fprintf(stderr, "No data!\n");
    exit(EXIT_FAILURE);
  }
  double sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum = sum + data[i];
    cum[i] = 100000.0 * sum / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  // Check the input data
  if (data == NULL) {
    fprintf(stderr, "No data!\n");
    exit(EXIT_FAILURE);
  }
  // check if dimension is 0, as there would be input after the for-loop
  if (n_countries == 0 || n_days == 0) {
    return;
  }
  unsigned max = 0;
  char * countryName = NULL;
  // for-loop to find the max value and its countryname
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max) {
        max = data[i][j];
        countryName = countries[i].name;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", countryName, max);
}
