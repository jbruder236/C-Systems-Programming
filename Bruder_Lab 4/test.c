#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


int countTokens(char* s,char delim)
{
   int cnt = 0;
   int inToken = *s != delim;
   while (*s) {
      if (*s == delim)
	    cnt += inToken;
      inToken = *s != delim;
      s++;
   }
   return cnt;
}

char* dupString(char* s, size_t len){
  char* duplicate = malloc(len*sizeof(char));
  duplicate[len-1] = 0; //Len-1?? - '\0'
  for(size_t i = 0; i < len; i++){
    duplicate[i] = s[i];
  }
  return duplicate;
}


int main(int argc, char* argv[])
{
    char* str = {"Hel--lo--o"};
    
    int count = countTokens(str, '-');
    
    printf("Count: %d\n", count);
    
    return 0;
}