#include <stdio.h>

int main(int argc, char* argv[])
{
   double total, count, x, average;
   
   while (scanf("%lf", &x) == 1) {
       total = x + total;
       count = count + 1;
       average = total/count;
       printf("Total=%lf Average=%lf\n", total, average);
   }
}
