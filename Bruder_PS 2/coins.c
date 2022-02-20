#include <stdio.h>
#define QUARTER 4
#define DIME 3
#define NICKEL 2
#define PENNY 1

int value(int coin){
  if(coin == QUARTER){
    return 25;
  }else if(coin == DIME){
    return 10;
  }else if(coin == NICKEL){
    return 5;
  }else{
    return 1;
  }
}

int count(int amount, int maxCoin){
    if(amount == 0){
        return 1;
    }
    if(amount < 0){
        return 0;
    }
    
  return 0;
}

int main(int argc, char* argv[]){
  int amount;
  printf("Enter amount: ");
  scanf("%d", &amount);
  printf("Number of ways to make %d cents: %d\n", amount, count(amount, QUARTER));
}
