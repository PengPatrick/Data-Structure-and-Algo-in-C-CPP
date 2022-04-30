#include "stats.h"
#include <stdio.h>
#include <string.h>


// any other headers you need here

stat_t parseLine(const char * line) {
  // STEP 1: write me
  // Check string is null of not
  if(line == NULL){
    perror("No line is read!");
    exit(EXIT_FAILURE);
  }

  stat_t sta;
  int countColon = 0;
  // Judge whether the line has two ":"
  for(size_t i = 0; line[i] != '\0'; i++){
    if(line[i] == ':'){
      countColon++;
    }
  }
  if(countColon != 2){
    perror("Wrong format of input information");
    exit(EXIT_FAILURE);
  }

  // Store the player's name
  size_t i = 0;
  for(; line[i] != ':'; i++){
    if(i > 62){
      perror("Name is too long!");
      exit(EXIT_FAILURE);
    }
    sta.player[i] = line[i];
  }
  if(i == 0){
    perror("No player's name in the input file!");
    exit(EXIT_FAILURE);
  }
  sta.player[i] = '\0';

  // Store the player's points
  size_t j = i + 1;
  int sum = 0;
  for(; line[j] != ':'; j++){
    if(line[j] < '0' || line[j] > '9'){
      perror("Wrong format of points!");
      exit(EXIT_FAILURE);
    }
    if(j == i + 2){
      if(line[j - 1] - '0' == 0){
	perror("Wrong format of points");
	exit(EXIT_FAILURE);
      }
    }
    sum = sum*10 + (line[j] - '0');
  }
  if((j-i-1) == 0){
    perror("No player's points in the input file!");
    exit(EXIT_FAILURE);
  }
  sta.points = (unsigned long) sum;

  // Store the game number
  size_t k = j + 1;
  sta.games = 0;
  for(; line[k] != '\0'; k++){
    if(line[k] < '0' || line[k] > '9'){
      perror("Wrong format of games!");
      exit(EXIT_FAILURE);
    }
    if(k == j + 2){
      if(line[k-1] - '0' == 0){
	perror("Wrong format of games!");
	exit(EXIT_FAILURE);
      }
    }
    sta.games = sta.games*10 + (line[k] - '0');
  }
  if((k-j-1) == 0){
    perror("No player's games in the input file!");
    exit(EXIT_FAILURE);
  }

  return sta;
}

double calcGamePerformance(stat_t * statarr, unsigned long * pointarr, size_t nplayers) {
  // STEP 2: write me
  // Check corner case. In fact, it is achieved in testing code.
  if(statarr == NULL || pointarr == NULL || nplayers < 1){
       perror("Invalid information!");
       exit(EXIT_FAILURE);
   }
   double sumAvg = 0.0;
   double sumOne = 0.0;
   for(size_t i = 0; i < nplayers; i++){
       sumAvg += ((double)statarr[i].points / (double)statarr[i].games);
       sumOne += pointarr[i];
   }
   return sumOne / sumAvg;
}

void addGameStats(stat_t * statarr, unsigned long * pointarr, size_t nplayers) {
  // STEP 3: write me
  // Check corner case. In fact, it is achieved in testing code.
  if(statarr == NULL || pointarr == NULL || nplayers < 1){
        perror("Invalid information!");
        exit(EXIT_FAILURE);
    }
    for(size_t i = 0; i < nplayers; i++){
      statarr[i].points += pointarr[i];
      statarr[i].games++;
    }
}

void printBreakout(stat_t * statarr, unsigned long * pointarr, size_t nplayers) {
  // STEP 4: write me
  // Check corner case. In fact, it is achieved in testing code.
  if(statarr == NULL || pointarr == NULL || nplayers < 1){
     perror("Invalid information!");
     exit(EXIT_FAILURE);
  }
  size_t maxIndex = 0;
  double max = 0.0;
  for(size_t i = 0; i < nplayers; i++){
     double pointAvg = ((double)statarr[i].points / (double)statarr[i].games);
     if(pointAvg == 0.0 && pointarr[i] > 0){
     //  If someone's avg is 0, but score larger than 0 in this game, it
     //  means that his improvement is infinity and he's the breakout player.
         maxIndex = i;
	 max = (double)pointarr[i] / pointAvg;
         break;
     }else if(pointAvg == 0.0 && pointarr[i] == 0){
       // If someone's avg is 0, and also score 0 in this game, it means that he
       // doesn't make changes, and he won't be the breakout player.
       continue;
     }else{
       // Check common cases: who make the greatest percentage of improvement will
       //                     be the breakout player.
       if((double)pointarr[i] / pointAvg >= max){
	 max = (double)pointarr[i] / pointAvg;
	 maxIndex = i;
       }
     }
  }
  // for both infinity and common cases, the 100.0*max will give correct answer. Infinity will give inf.
  printf("The breakout player this game is %s with %.0f%% of avg ppg\n", statarr[maxIndex].player, 100.0*max);
}
