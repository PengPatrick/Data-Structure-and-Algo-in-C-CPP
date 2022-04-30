#ifndef __RETIREMENT_H__
#define __RETIREMENT_H__

#include <stdlib.h>

// Struct to hold time of year and month
struct date_tag {
  unsigned year;
  unsigned month;
};
typedef struct date_tag date_t;

// Struct to hold dates, S&P and Bonds information
struct ret_info_tag{
  date_t *dates;
  double *idxs;
  double *divs;
  double *bonds;
};
typedef struct ret_info_tag ret_info;

// Struct to hold array of dates and cumulative investments
// (hint: can be used for any investment strategy)
struct ret_portfolio_tag {
  date_t * dates;
  double *cum_invest_sp;
  double *cum_invest_bond;
  double *cum_invest_mix;
  //size_t n;
};
typedef struct ret_portfolio_tag ret_portfolio_t;


// Parse the input string into time, check the time format, and store in struct
// Return a struct of date
date_t parseTime(char *time);

// Count the number of dot in input string
int countDot(char *str);

// Count the number of comma in input string
int countComma(char *str);

// Check if input string can transfer to double
void checkNumber(char *str);

// Read the S&P file, pass a line of string to "parseSp" function for getting information and storing.
// Return the number of lines of S&P file
int readSp(char *name, ret_info *retirement);

// Parse the input string and store dates and S&P information in struct
void parseSp(char *str, ret_info *retirement, int index);

// Read the bonds file, pass a line of string to "parseBond" function for getting information and storing
// Return the number of lines of S&P file
int readBond(char *name, ret_info *retirement);

// Parse the input string and store dates and bonds information in struct
void parseBond(char *str, ret_info *retirement, int index);

// Strategy 1, read realated S&P information and calculate the expected portfolio
void calSp(date_t start, int durations, int count, ret_info *retirement, ret_portfolio_t *portfolio);

// Strategy 2, read realated bonds information and calculate the expected portfolio
void calBond(date_t start, int durations, int count, ret_info *retirement, ret_portfolio_t *portfolio);

// Strategy 3, read realated S&P and bonds information and calculate the expected portfolio
void calMix(date_t start, int durations, int count, ret_info *retirement, ret_portfolio_t *portfolio);

// For all portfolio information, write into a csv file called "portfolio.csv"
void writeFile(ret_portfolio_t *portfolio, int durations);

// Prevent memory leak brought by struct
void freeRetirement(ret_info *retirement);

// Prevent memory leak brought by struct
void freePortfolio(ret_portfolio_t *portfolio);

#endif

