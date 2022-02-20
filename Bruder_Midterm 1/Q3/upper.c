#include <stdio.h>
#include <stdlib.h>

int lengthOfS(char* str){
    int i = 0;
    
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

char* strupper(char* s)
{
   int length = lengthOfS(s);
   int i = 0;
   int temp;
   
   char* str;
   
   str = (char*)malloc(sizeof(char)*length);
   
   for(i = 0; i < length; i++){
       temp = (int)s[i];
       if(temp >= 97 && temp <= 122){
           temp = temp - 32;
       }
       str[i] = (char)temp;
   }
   
   return str;
}
