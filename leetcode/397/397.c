#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long min(long a, long b) {
  return (a < b ? a : b);
}

long min_step(long n) {
  if(n == 1) {
    return 0;
  }
  else if(n % 2 == 0) {
    return 1 + min_step(n/2);
  }
  else {
    return 1 + min(min_step(n+1), min_step(n-1));
  }
}

long solve() {
  long n;
  scanf("%ld", &n);

  printf("%ld", min_step(n));
  //printf("%ld", INT_MAX);
}

int main() {

  solve();
}
