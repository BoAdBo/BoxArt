#include <stdio.h>
#include <stdbool.h>
bool calculated[1200];
int mem[1200];// the question stated that the size won't exceeds 1000

int min(int a, int b) {
  return (a < b ? a : b);
}

int f(int *cost, int end, int i) {
  if(i + 2 > end) {
    return cost[i];
  }
  else {
    int x1, x2;
    if(calculated[i+1]) x1 = mem[i+1];
    else {
      mem[i+1] = f(cost, end, i+1);
      x1 = mem[i+1];
      calculated[i+1] = true;
    }
    if(calculated[i+2]) x2 = mem[i+2];
    else {
      mem[i+2] = f(cost, end, i+2);
      x2 = mem[i+2];
      calculated[i+2] = true;
    }

    return cost[i] + min(x1, x2);
  }
}

int minCostClimbingStairs(int* cost, int costSize) {
  // use memorization in order to avoid exponential growth
  for(int i = 0; i < costSize; ++ i) {
    calculated[i] = false;
  }

  return min(f(cost, costSize-1, 0), f(cost, costSize-1, 1));
}

/* int main() { */
/*   int array[] = {0,0,1,1}; */
/*   printf("%d", minCostClimbingStairs(array, 4)); */
/* } */
