#include <stdio.h>
#include <assert.h>

double leibnizRecurrent(int n)
{
    double temp = -1;
    double tempn = n;
    double result = 1;
    while (tempn != 0) {
        result *= temp;
        --tempn;
    }
    if(n == 0){
        return 1;
    }
    else{
        return (result/(2*n+1)) + leibnizRecurrent(n-1);
    }
}

double leibnizIterative(int n)
{
    double sum = 0;
    int k = 0;
    for(k = 0; k <= n; k++){
        double x = k;
        if(k % 2 == 0){
            sum = sum + (1/(2*x+1));
        }
        else{
            sum = sum + (-1/(2*x+1));
        }
    }
    return sum;
}

int main(int argc, char* argv[]){
  if(argc != 3){
    printf("Usage: ./pi <mode> <n>, where <mode> is 1 for recurrent version, and 2 is for the iterative version, and n is the upper bound of the summation.\n");
  }else{
    int mode = 0, n = 0;
    double pi = 0;
    assert(sscanf(argv[1], "%d", &mode) == 1);
    assert(sscanf(argv[2], "%d", &n) == 1);
    assert(mode == 1 || mode == 2);
    assert(n >= 0);
    if(mode == 1){
      pi = 4*leibnizRecurrent(n);
    }else{
      pi = 4*leibnizIterative(n);
    }
    printf("PI: %f\n", pi);
  }
  return 0;
}
