#include "calendar.h"
#include <stdio.h>

int main(){
  /*
    Here we want to count the number of sundays that fall on the first of the month. 
    Start with the first of January start year, and count forward until we get to december of the end year 
   */
  int startYear, weekDay, endYear;
  printf("Enter start year: ");
  scanf("%d", &startYear);
  printf("Enter day of January 1st in that year (0 = sunday, 1 = Monday, ..., 6 = saturday): ");
  scanf("%d", &weekDay);
  printf("Enter end year: ");
  scanf("%d", &endYear);

  int numSundays = numFirstSundays(startYear, endYear, weekDay);
  printf("Number of sundays: %d\n", numSundays);
    
}
