#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int comp(const void *elem1, const void *elem2) {
  int f = *((int*)elem1);
  int s = *((int*)elem2);

  if(f > s) return 1;
  else if(f < s) return -1;
  return 0;
}

int findNoGreater(int key, int *array, int l, int h) {
  if(l < h) {
    int mid = (l+h)/2;
    if(array[mid] >= key) {
      return findNoGreater(key, array, l, mid);
    }
    else {
      return findNoGreater(key, array, mid+1, h);
    }
  }
  else {
    if(l == h && key <= array[l]) {
      return array[l];
    }
  }

  // not found
  return -1;
}

int findNoSmaller(int key, int *array, int l, int h) {
  if(l < h) {
    int mid = (l+h+1)/2;
    if(array[mid] <= key) {
      return findNoSmaller(key, array, mid, h);
    }
    else {
      return findNoSmaller(key, array, l, mid-1);
    }
  }
  else {
    if(l==h && key >= array[l]) {
      return array[l];
    }
  }

  return -1;
}

int min(int a, int b) {
  return (a < b ? a : b);
}

int findRadius(int* houses, int housesSize, int* heaters, int heatersSize) {
  qsort(heaters, heatersSize, sizeof(int), comp);

  //int* nearest = (int*)malloc(sizeof(int)*housesSize);
  int max = INT_MIN;

  for(int i = 0; i < housesSize; ++ i) {
    int left = findNoSmaller(houses[i], heaters, 0, heatersSize-1);
    int right = findNoGreater(houses[i], heaters, 0, heatersSize-1);
    int less;
    //printf("(%d, %d)\n", right, left);
    if(right > 0 && left > 0) {
      less = min(right - houses[i], houses[i] - left);
    }
    else if(right > 0) {
      less = right - houses[i];
    }
    else if(left > 0){
      less = houses[i] - left;
    }
    //    printf("%d\n", less);

    max = max > less ? max : less;
  }
  return max;
  //  printf("%d", max);
}

/* int main() { */
/*   //  int x[] = {4,5,2,1,0,9,8,6,7}; */

/*   //qsort (x, sizeof(x)/sizeof(int), sizeof(*x), comp); */

/*   /\* for(int i = 0; i < sizeof(x)/sizeof(int); ++ i) { *\/ */
/*   /\*   printf("%d ", x[i]); *\/ */
/*   /\* } *\/ */
/*   /\* printf("\n"); *\/ */

/*   /\* printf("%d", findNoSmaller(3, x, 0, 8)); *\/ */

/*   int x1[] = {1,2,3}; */
/*   int x2[] = {2}; */
/*   printf("results: %d", findRadius(x1, 3, x2, 1)); */
/* } */
