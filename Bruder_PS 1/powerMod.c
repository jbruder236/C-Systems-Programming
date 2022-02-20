#include <stdio.h>

int main(int argc, char* argv[]){
   printf("Enter n, e and m: ");
   int n, e, m, val;
   scanf( "%i %i %i", &n, &e, &m);
   val = 1;
   n = n%m;
   while(e > 0){

   
        if(e % 2 != 0){
            val = (val*n)%m;
            }
       //printf("temp=%i m=%i\n", temp, m);
        
   
        e = e>>1;
        n = (n*n)%m;
        
        }
   
   printf("%i ** %i mod %i = %i\n", n, e, m, val);
}
