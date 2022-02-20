#include "analyze.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void analyzeURL(char* url,char* host,int* port,char* doc)
{
   char check[2] = "/:";
   char* str;
   char* elems[3];
   
   str = strtok(url, check);
   int i = 0;
   
   do{
       if(str[0] == 'h' && str[1] == 't'){
           int w;
           str = strtok(NULL, "/:");
       }
       else if(i == 0){
           //printf("host = %s\n", str);
           strcpy(host, str);
           i += 1;
           str = strtok(NULL, ":/");
       }
       
       
       else if(i == 1){
           //printf("%c\n", url[0]);
           int temp = atoi(str);
           if(temp == 0){
               char* temp = "/";
               strcpy(doc, temp);
               strcat(doc, str);
               //printf("doc = %s\n", str);
               i+=3;
           }
           else{
               //printf("port = %s\n", str);
               *port = temp;
               i += 1;
               str = strtok(NULL, ":");
           }
       }
       else{
           char* temp = "/";
               strcpy(doc, temp);
               strcat(doc, str);
           //printf("doc = %s\n", str);
           i += 4;
           //str = strtok(NULL, check);
       }
       
   }while(i < 3);


   
}