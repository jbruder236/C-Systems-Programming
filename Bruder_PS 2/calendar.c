#include <stdio.h>
#include "calendar.h"

int numDaysInMonth(int month, int year){
  /*
    
   */
  switch(month){
  case JAN:
    return 31;
    break;
  case FEB:
    if(year%100 == 0){ //if century
        if(year%400 == 0){
            return 29;
            break;
        }
        else{
            return 28;
            break;
        }
    }
    else if(year%4 == 0){
        return 29;
        break;
    }
    else{
        return 28;
        break;
    }
  case MAR:
    return 31;
    break;
  case APR:
    return 30;
    break;
  case MAY:
    return 31;
    break;
  case JUN:
    return 30;
    break;
  case JUL:
    return 31;
    break;
  case AUG:
    return 31;
    break;
  case SEP:
    return 30;
    break;
  case OCT:
    return 31;
    break;
  case NOV:
    return 30;
    break;
  case DEC:
    return 31;
    break;
     /*
      TODO: Add the cases for February through December. Don't forget about leap years. 
      For years that are not centuries (i.e. not 1900, 2000), it is a leap year if it is disible by 4.
      For years that are centuries, it is a leap year if it is divisible by 400.
      Return -1 if the month doesn't fit any of the cases. 
     */
  default:
    return -1;
  }
}

int numFirstSundays(int startYear, int endYear, int janFirstWeekday)
{
    int iyear = 0;
    int imonth = 0;
    int weekday = janFirstWeekday;
    int sundayCount = 0;
    
    for(iyear = startYear; iyear < endYear; iyear++){
        for(imonth = JAN; imonth <= DEC; imonth++){
            if(weekday == SUNDAY){
                sundayCount++;
            }
            if(imonth == DEC){
                weekday = (weekday + numDaysInMonth(JAN, iyear+1)) % 7;
            }
            else{
                weekday = (weekday + numDaysInMonth(imonth+1, iyear)) % 7;
            }
        }
    }
    return sundayCount;
}
