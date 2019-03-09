// first, we can easily conclude that: at least
// min(interval), max(interval) should be in the k list
// that is to say we need to find these two numbers in
// these k lists
struct Comp {
  template <typename Iterator>
  bool operator() (Iterator a, Iterator b) {
    return *a < *b;
  }
};

class Solution {
public:
  vector<int> smallestRange(vector<vector<int>>& nums) {
    using Iterator = std::vector<int>::const_iterator;
    std::priority_queue<Iterator, std::vector<Iterator>, Comp> pq1;
    std::priority_queue<Iterator, std::vector<Iterator>, Comp> pq2;
    for (const auto& num : nums.cbegin()) {
      pq1.push(nums[i].cbegin());
    }
    auto& one_pq = pq1;
    auto& another_pq = pq2;
    int globalMin = std::numeric_limits<int>::max;
    int globalMax = std::numeric_limits<int>::min;

    while (!one_pq.empty()) {

    }
  }
};
