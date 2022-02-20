#include <stdio.h>

int main(int argc, char* argv[]){
   printf("n = ");
   int n;
   scanf("%d", &n);
   
   double i;
   double total = 0;
   for(i = 0; i <= n; ++i){
       double ptemp = 1;
       int w;
       for(w = 0; w < i; ++w){
           ptemp = ptemp * 16;
       }
       
       total = total + (((4/(8*i+1))-(2/(8*i+4))-(1/(8*i+5))-(1/(8*i+6)))*(1/ptemp));
   }
   printf("PI = %lf", total);
}
