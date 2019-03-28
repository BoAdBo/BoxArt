class Solution {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    // using sieve would be a toll to ram
    // use generation from the previous ugly numbers.
    std::vector<int> index(primes.size(), 0);
    std::vector<int> val(primes.size(), 1);
    std::vector<int> uglyNums(n, std::numeric_limits<int>::max());

    // less multiplication operations
    int next = 1;
    for (std::size_t i = 0; i < uglyNums.size(); ++ i) {
      uglyNums[i] = next;
      next = std::numeric_limits<int>::max();
      for (std::size_t j = 0; j < primes.size(); ++ j) {
        if (val[j] == uglyNums[i]) {
          val[j] = uglyNums[index[j]] * primes[j];
          ++index[j];
        }
        next = std::min(val[j], next);
      }
    }
  return uglyNums.back();
  }
};
