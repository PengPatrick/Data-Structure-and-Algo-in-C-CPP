# include <stdio.h>
# include <stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working,
		retire_info retired){
  double money = initial;
  if(working.months > 0){
    for(int i = 0; i < working.months; i++){
      printf("Age %3d month %2d you have $%.2lf\n", (i + startAge)/12, (i + startAge) % 12, money);
      money = money * (1 + working.rate_of_return) + working.contribution;
    }
  }
  int retireAge = startAge + working.months;
  if(retired.months > 0){
    for(int j = 0; j < retired.months; j++){
      printf("Age %3d month %2d you have $%.2lf\n", (j + retireAge)/12, (j + retireAge) % 12, money);
      money = money * (1 + retired.rate_of_return) + retired.contribution;
    }
  }
}

int main(){
  retire_info working = {489, 1000, 0.045/12};
  retire_info retired = {384, -4000, 0.01/12};
  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
