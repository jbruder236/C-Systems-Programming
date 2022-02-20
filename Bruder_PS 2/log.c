#include <stdio.h>


double approxLog(double a, int n)
{
    double deltaX = (a-1)/n;
    int i = 0;
    double pastH;
    double curH;
    double sum = 0;
    
    sum = ((1/(1 + n*deltaX)) + 1)/2;
    
    pastH = 1 + deltaX; 
    
    for(i = 1; i < n; i++){
        sum = sum + (1/(1 + i*deltaX));
        pastH = curH;
    }
    return deltaX*sum;
}

int main(int argc, char* argv[])
{
  
  double a;
  int n;
  printf("Enter a: ");
  scanf("%lf", &a);
  printf("Enter n: ");
  scanf("%d", &n);
  double logarithm = approxLog(a, n);
  printf("Natural logarithm: %lf\n", logarithm);
  return 0;
}
