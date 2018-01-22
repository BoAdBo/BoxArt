#include <stdlib.h>
#include <stdio.h>

/*
  This is the naive implementation
 */
int findWarmer(int *temp, int size, int current) {
  int cur_temp = temp[current];
  for(int i = current+1; i < size; ++ i) {
    if(temp[i] > cur_temp) {
      return i;
    }
  }
  // not found
  return -1;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize,
                       int* returnSize) {
  *returnSize = temperaturesSize;
  int *result = (int*)malloc(sizeof(int)*(*returnSize));

  for(int i = 0; i < *returnSize; ++ i) {
    int index = findWarmer(temperatures, temperaturesSize, i);
    if(index > 0) {
      result[i] = index - i;
    }
    else {
      result[i] = 0;
    }
  }

  return result;
}

/* int main() { */
/*   int x[] = {73,74,75,71,69,72,76,73}; */
/*   int p = 8; */
/*   int *l; */
/*   l = dailyTemperatures(x, 8, &p); */
/*   for(int i = 0; i < 8; ++ i) { */
/*     printf("%d ", l[i]); */
/*   } */
/* } */
