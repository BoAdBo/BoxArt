class Solution {
 public:
  double myPow(double x, int n) {
    // could overflow
    long N = n;
    if (n < 0) {
      x = 1.0 / x;
      N = -N;
    }
    double res = 1.0;
    for (long i = N; i > 0; i /= 2) {
      if (i % 2 == 1) {
        res = res * x;
      }
      x *= x;
    }
    return res;
  }
};
