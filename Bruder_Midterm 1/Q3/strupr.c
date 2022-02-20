#include "upper.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
   char* line = NULL;
   size_t len = 0;
   if (getline(&line,&len,stdin) == 0) {
      exit(1); // bad input
   }
   char* up = strupper(line);
   printf("[%s]\n",up);
   free(line);
   return 0;
}
