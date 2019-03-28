class Solution {
 public:
  int nthSuperUglyNumber(int n, const vector<int>& primes) {
    // using sieve would be a toll to ram
    // use generation from the previous ugly numbers.
    // std::vector<int> index(primes.size(), 0);

    using Index = std::pair<std::size_t, std::size_t>;
    // first: prime, second: index of ugly number
    std::vector<int> uglyNums(n, std::numeric_limits<int>::max());
    auto cmp = [&uglyNums] (const Index& a, const Index& b) {
                 // since we want the opposite, smallest at the front
                 return uglyNums[a.second] * a.first > uglyNums[b.second] * b.first;
               };
    std::priority_queue<Index, std::vector<Index>, decltype(cmp)> minHeap(cmp);
    for (std::size_t j = 0; j < primes.size(); ++ j) {
      minHeap.emplace(primes[j], 0);
    }
    uglyNums.front() = 1;
    for (std::size_t i = 1; i < uglyNums.size(); ++ i) {

      // pick the smallest from the candidates
      auto min = minHeap.top();
      uglyNums[i] = min.first * uglyNums[min.second];

      // skip duplicates
      while (min.first * uglyNums[min.second] <= uglyNums[i]) {
        minHeap.pop();
        ++min.second;
        minHeap.push(min);
        min = minHeap.top();
      }
    }
  return uglyNums.back();
  }
};
