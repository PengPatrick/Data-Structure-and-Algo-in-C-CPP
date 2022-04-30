#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "retirement.h"


date_t parseTime(char *time){
    if(time == NULL){
      perror("No time is read!");
      exit(EXIT_FAILURE);
    }
    date_t date;
    // Time must has one dot, check it
    int countDot = 0;
    for(size_t i = 0; time[i] != '\0'; i++){
      if(time[i] == '.'){
          countDot++;
      }
    }
    if(countDot != 1){
      perror("Wrong format of time!");
      exit(EXIT_FAILURE);
    }
    // Check year format, year should have value and it is number, read year
    size_t i = 0;
    date.year = 0;
    for(; time[i] != '.'; i++){
      if(!isdigit(time[i])){
          perror("Wrong format of time!");
          exit(EXIT_FAILURE);
      }
      date.year = date.year * 10 + (time[i] - '0');
    }
    if(i == 0){
      perror("No input year!");
      exit(EXIT_FAILURE); 
    }
    // Check month format, month should have value and it is number, range from 01 (or 1) to 12, read month
    size_t j = i + 1;
    date.month = 0;
    for(; time[j] != '\0'; j++){
      if(!isdigit(time[j])){
          perror("Wrong format of time!");
          exit(EXIT_FAILURE);
      } 
      date.month = date.month * 10 + (time[j] - '0');
    }
    if(j == i + 1){
      perror("No input month!");
      exit(EXIT_FAILURE);
    }
    // Month format like 001 is unacceptable.
    if(j - i > 3){
      perror("Wrong format of month!");
      exit(EXIT_FAILURE);
    }
    if(date.month == 0 || date.month > 12){
      perror("Wrong format of month!");
      exit(EXIT_FAILURE);
    }
    return date;
}


int countDot(char *str){
    int countDot = 0;
    for(size_t i = 0; str[i] != '\0'; i++){
      if(str[i] == '.'){
        countDot++;
      }
    }
    return countDot;
}


int countComma(char *str){
    int countComma = 0;
    for(size_t i = 0; str[i] != '\0'; i++){
        if(str[i] == ','){
            countComma++;
        }
    }
    return countComma;
}


void checkNumber(char *str){
  for(size_t i = 0; str[i] != '\0' && str[i] != '\r'; i++){
    if(str[i] == '.' || str[i] == ',' || str[i] == ' '){
      continue;
    }
    if(!isdigit(str[i])){
      perror("Invalid content in files!");
      exit(EXIT_FAILURE);
    }
  }
}


int readSp(char *name, ret_info *retirement){
    FILE *f = fopen(name, "r");
    if(f == NULL){
      perror("No file!");
      exit(EXIT_FAILURE);
    }
    size_t count = 0;
    char **arr = NULL;
    char *line = NULL;
    size_t sz = 0;

    // Read the file and count the number of lines of file
    while(getline(&line, &sz, f) >= 1){
      count++;
      arr = realloc(arr, count*sizeof(*arr));
      arr[count-1] = line;
      line = NULL;
    }
    free(line);

    // Allocate memory on the heap for struct to store information
    retirement->dates = malloc((count-1)*sizeof(*retirement->dates));
    retirement->idxs = malloc((count-1)*sizeof(*retirement->idxs));
    retirement->divs = malloc((count-1)*sizeof(*retirement->divs));

    free(arr[0]);
    // For useful information, pass to "parseSp" function, for useless information, free the memory
    for(size_t i = 1; i < count; i++){
      parseSp(arr[i], retirement, i-1);
      free(arr[i]);
    }
    free(arr);

    if(fclose(f) == EOF){
      perror("Fail to close the file!");
      exit(EXIT_FAILURE);
    }
    return count - 1;
}


void parseSp(char *str, ret_info *retirement, int index){
    char *token;
    int i = 0;
    char *arr[3];
    // Check the string, to make sure it contains 2 comma
    //int countdot = countDot(str);
    int countcomma = countComma(str);
    if(countcomma != 2){
       perror("Invalid lines in Sp!");
       exit(EXIT_FAILURE);
    }
    // Use comma as dividen to get substring
    while((token = strtok_r(str, ",", &str))){
       arr[i++] = token;
    }
    // Check substring format, make the string into double format with "strtod"
    checkNumber(arr[0]);
    checkNumber(arr[1]);
    checkNumber(arr[2]);
    // Store S&P information in the struct
    retirement->dates[index] = parseTime(arr[0]);
    if(index > 0){
      if(retirement->dates[index - 1].month == 9){
	retirement->dates[index].month = 10;
      }
      // Check if time is continuous
      if(retirement->dates[index].year * 12 + retirement->dates[index].month - retirement->dates[index - 1].year * 12 - retirement->dates[index - 1].month != 1){
        perror("The date isn't continuous!");
        exit(EXIT_FAILURE);
      }
    }
    retirement->divs[index] = strtod(arr[2], NULL);
    retirement->idxs[index] = strtod(arr[1], NULL);
}


int readBond(char *name, ret_info *retirement){
    FILE *f = fopen(name, "r");
    if(f == NULL){
      perror("No file!");
      exit(EXIT_FAILURE);
    }
    size_t count = 0;
    char **arr = NULL;
    char *line = NULL;
    size_t sz = 0;

    // Read the file and count the number of lines of file
    while(getline(&line, &sz, f) >= 1){
      count++;
      arr = realloc(arr, count*sizeof(*arr));
      arr[count-1] = line;
      line = NULL;
      if(count - 1 >= 592){
        count--;
        free(arr[count]);
      }
    }
    free(line);

    // Allocate memory on the heap for struct to store information
    retirement->bonds = malloc((count-1)*sizeof(*retirement->dates));

    free(arr[0]);
    // For useful information, pass to "parseSp" function, for useless information, free the memory
    for(size_t i = 1; i < count; i++){
      parseBond(arr[i], retirement, i-1);
      free(arr[i]);
    }
    free(arr);

    if(fclose(f) == EOF){
      perror("Fail to close the file!");
      exit(EXIT_FAILURE);
    }
    return count - 1;  
}


void parseBond(char *str, ret_info *retirement, int index){
    // Bond(t) is after the first comma, store it in the struct
    char *token;
    date_t datecheck;
    int i = 0;
    char *arr[2];
    // Check the string, to make sure it contains 2 dot and 1 comma
    //int countdot = countDot(str);
    int countcomma = countComma(str);
    if(countcomma != 1){
      perror("Invalid lines in Bond!");
      exit(EXIT_FAILURE);
    }

    while((token = strtok_r(str, ",", &str))){
      arr[i++] = token;
    }
    // Check subtring format
    checkNumber(arr[0]);
    checkNumber(arr[1]);
    
    retirement->bonds[index] = strtod(arr[1], NULL);
    datecheck = parseTime(arr[0]);
    // Compare bond date with sp date
    if(datecheck.year != retirement->dates[index].year || datecheck.month != retirement->dates[index].month){
      perror("Two files cannot match!");
      exit(EXIT_FAILURE);
    }
}


void calSp(date_t start, int durations, int count, ret_info *retirement, ret_portfolio_t *portfolio){
    int startIdx = 0;
    double sum = 0.0;
    portfolio->dates = malloc((durations) * sizeof(*portfolio->dates));
    portfolio->cum_invest_sp = malloc((durations) * sizeof(*portfolio->cum_invest_sp));
    
    // Find the start index and to do the calculation 
    for(int i = 0; i < count; i++){
      if(retirement->dates[i].year * 12 + retirement->dates[i].month == start.year * 12 + start.month){
          startIdx = i;
      }
    }
    startIdx++;
    
    // Use strategy 1 : total S&P to calculate the portfolio, then store in a struct called "portfolio"
    for(int i = startIdx; i < startIdx + durations; i++){
      double ror = retirement->idxs[i] / retirement->idxs[i - 1] - 1 + (retirement->divs[i] / 12) / retirement->idxs[i];
      sum = sum*(1 + ror) + 100*pow(1.025, retirement->dates[i].year - retirement->dates[startIdx].year);
      portfolio->dates[i - startIdx]= retirement->dates[i];
      portfolio->cum_invest_sp[i - startIdx] = sum;
    }
}


void calBond(date_t start, int durations, int count, ret_info *retirement, ret_portfolio_t *portfolio){
    int startIdx = 0;
    double sum = 0.0;

    portfolio->cum_invest_bond = malloc((durations) * sizeof(*portfolio->cum_invest_bond));
    // Find the start index and to do the calculation
    for(int i = 0; i < count; i++){
      if(retirement->dates[i].year*12 + retirement->dates[i].month == start.year*12 + start.month){
        startIdx = i;
      }
    }
    startIdx++;
    // Use strategy 2 : bonds to calculate the portfolio, then store in a struct called "portfolio"
    for(int i = startIdx; i < startIdx + durations; i++){
      double ror = retirement->bonds[i] / 12 / 100;
      sum = sum*(1 + ror) + 100*pow(1.025, retirement->dates[i].year - retirement->dates[startIdx].year);
      portfolio->cum_invest_bond[i - startIdx] = sum;
    }
}


void calMix(date_t start, int durations, int count, ret_info *retirement, ret_portfolio_t *portfolio){
    int startIdx = 0;
    double sum = 0.0;

    portfolio->cum_invest_mix = malloc((durations) * sizeof(*portfolio->cum_invest_mix));
    // Find the start index and to do the calculation
    for(int i = 0; i < count; i++){
      if(retirement->dates[i].year*12 + retirement->dates[i].month == start.year*12 + start.month){
        startIdx = i;
      }
    }
    startIdx++;
    // Use strategy 3 : lifecycle to calculate the portfolio, then store in a struct called "portfolio"
    for(int i = startIdx; i < startIdx + durations; i++){
      double ror_sp = retirement->idxs[i] / retirement->idxs[i - 1] - 1 + (retirement->divs[i] / 12) / retirement->idxs[i];
      double ror_bond = retirement->bonds[i] / 12 / 100;
      sum = sum * (1 + ror_sp)*(1 - 0.02 * (retirement->dates[i].year - retirement->dates[startIdx].year)) +
	    sum * (1 + ror_bond) * 0.02 * (retirement->dates[i].year - retirement->dates[startIdx].year) +
	    100 * pow(1.025, retirement->dates[i].year - retirement->dates[startIdx].year);
      portfolio->cum_invest_mix[i - startIdx] = sum;
    }
}


void writeFile(ret_portfolio_t *portfolio, int durations){
    FILE *f;
    f = fopen("portfolio.csv", "w+");
    
    for(int i = 0; i < durations; i++){
      fprintf(f, "%u.%02u,%.2f,%.2f,%.2f\n", portfolio->dates[i].year, portfolio->dates[i].month, portfolio->cum_invest_sp[i], portfolio->cum_invest_bond[i], portfolio->cum_invest_mix[i]);
    }

    if(fclose(f) == EOF){
      perror("Fail to close the file!");
      exit(EXIT_FAILURE);
    }
}


void freeRetirement(ret_info *retirement){
    // Free the entire retirement struct
    free(retirement->dates);
    free(retirement->divs);
    free(retirement->idxs);
    free(retirement->bonds);
    free(retirement);
}


void freePortfolio(ret_portfolio_t *portfolio){
    // Free the entire portfolio struct
    free(portfolio->dates);
    free(portfolio->cum_invest_sp);
    free(portfolio->cum_invest_bond);
    free(portfolio->cum_invest_mix);
    free(portfolio);
}


int main(int argc, char** argv){
    if(argc != 5){
        perror("Wrong number of command arguments!");
        exit(EXIT_FAILURE);
    }
    int countSp = 0;
    int countBond = 0;
    int durations = 0;

    ret_info *retirement;
    ret_portfolio_t *portfolio;
    retirement = malloc(sizeof(*retirement));
    portfolio = malloc(sizeof(*portfolio));

    // 1. read the S&P 500 index level
    countSp = readSp(argv[1], retirement);
    // 2. read the bond rates
    countBond = readBond(argv[2], retirement);
    if(countSp != countBond){
      perror("Two given files have errors!");
      exit(EXIT_FAILURE);
    }
    // 3. read the start date
    date_t start = parseTime(argv[3]);
    // 4. read the end date
    date_t end = parseTime(argv[4]);

    durations = end.year*12 + end.month - start.year*12 - start.month;
    // Gurantee that start time is ealier than end time
    if(durations <= 0){
      perror("Input time range is invalid!");
      exit(EXIT_FAILURE);
    }
    if(retirement->dates[0].year * 12 + retirement->dates[0].month > start.year * 12 + start.month){
      perror("Start date out of range!");
      exit(EXIT_FAILURE);
    }
    if(retirement->dates[countSp-1].year * 12 + retirement-> dates[countSp-1].month < end.year * 12 + end.month){
      perror("End date out of range!");
      exit(EXIT_FAILURE);
    }
    // Calculate 3 strategy and write into portfolio struct
    calSp(start, durations, countSp, retirement, portfolio);
    calBond(start, durations, countBond, retirement, portfolio);
    calMix(start, durations, countSp, retirement, portfolio);
    // Write result into "portfolio.csv"
    writeFile(portfolio, durations);
    // Free the memory
    freeRetirement(retirement);
    freePortfolio(portfolio);
    return EXIT_SUCCESS;
}
