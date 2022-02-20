#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct TokenArray{
  char** tokens;
  size_t numTokens;
} TokenArray;

char* dupString(char* s, size_t len){
  char* duplicate = malloc((len+1)*sizeof(char));
  duplicate[len] = 0;
  for(size_t i = 0; i < len; i++){
    duplicate[i] = s[i];
  }
  return duplicate;
}

int countTokens(char* s,char delim)
{
   int cnt = 1;
   int inToken = *s != delim;

   while (*s) {
      if (*s == delim)
	    cnt += inToken;
      inToken = *s != delim;
      s++;
   }
   if(*(s-1) == delim)
      cnt--;
   return cnt;
}

char* tokenEnd(char* from,char delim)
{
   while (*from && *from != delim) from++;
   return from;                              //change for correct te, ts
}

char* skipDelim(char* from,char delim)
{
   while(*from && *from == delim) from++;
   return from;
}

TokenArray tokenize(char* string, char delim)
{
  size_t numTok = countTokens(string,delim);       //
  char** tokens = malloc(sizeof(char*)*numTok);    //
  size_t tokenIndex = 0;                           //
  char* ts = string;                               //ts is equal to string
  while(tokenIndex < numTok) {                     //while index < 3     0,1,2
     char* te = tokenEnd(ts,delim);
     //printf("Te: %s      Ts: %s\n", te, ts);
     //printf("Te-ts+1: %ld\n", te-ts+1);
     tokens[tokenIndex] = dupString(ts,te-ts);   //ts is the string
     //printf("Token added: %s\n", tokens[tokenIndex]);
     ts = skipDelim(te,delim);
     tokenIndex++;
  }
  TokenArray ta;
  ta.tokens = tokens;
  ta.numTokens = numTok;
  return ta;
}

int main(int argc, char* argv[])
{
  printf("Enter string:\n");
  char* string = NULL;
  size_t n = 0;
  ssize_t lineSize = getline(&string, &n, stdin);
  string[lineSize - 1] = '\0';
  printf("Enter delimiter: ");
  char delim;
  assert(scanf("%c", &delim) == 1);

  TokenArray ta = tokenize(string, delim);
  printf("Num tokens: %lu\n", ta.numTokens);
  for(size_t i = 0; i < ta.numTokens; i++){
    printf("token: %s\n", ta.tokens[i]);
    free(ta.tokens[i]);
  }
  free(ta.tokens);
  free(string);
  
  return 0;
}
 
