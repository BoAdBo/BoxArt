class Solution {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    // using sieve would be a toll to ram
    // use generation from the previous ugly numbers.
    std::vector<int> index(primes.size(), 0);
    std::vector<int> uglyNums(n, std::numeric_limits<int>::max());
    uglyNums.front() = 1;
    for (std::size_t i = 1; i < uglyNums.size(); ++ i) {

      // pick the smallest from the candidates
      for (std::size_t j = 0; j < primes.size(); ++ j) {
        uglyNums[i] = std::min(primes[j] * uglyNums[index[j]], uglyNums[i]);
      }

      // skip duplicates, since uglyNums is the current smallest
      for (std::size_t j = 0; j < primes.size(); ++ j) {
        while (primes[j] * uglyNums[index[j]] <= uglyNums[i]) ++index[j];
      }
    }
  return uglyNums.back();
  }
};
