#include "strip.h"
#include <stdio.h>
#include <stdlib.h>
/* You cannot add more header files */
/* Any auxiliary function you need, you must implement */

int lengthOfS(char* str){
    int i = 0;
    
    while(str[i] != '\0'){
        i++;
    }
    return i;
}


char* strip(char* s)
{
   int i = 0;
   int found = 1;
   char temp;
   int length = lengthOfS(s);
   
   char space = ' ';
   char tab = '\t';
   char lf = '\n';
   char cr = '\r';
   
   while(found){
       temp = s[i];
       if(temp == space || temp == tab || temp == lf || temp == cr){
           if(s[i+1] == space || s[i+1] == tab || s[i+1] == lf || s[i+1] == cr){
               s[i] = '\0';
               found = 0;
           }
       }
       if(i > length) {
           found = 0;
       }
       i++;
   }

   return s; /* you should modify this line of course */
}


