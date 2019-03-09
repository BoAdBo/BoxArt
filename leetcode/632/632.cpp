struct Comp {
  // since it's a priority queue
  template <typename Iterator>
  bool operator() (const std::pair<Iterator, Iterator>& a,
                   const std::pair<Iterator, Iterator>& b) {
    return *(a.first) >= *(b.first);
};

class Solution {
public:
  vector<int> smallestRange(vector<vector<int>>& nums) {
    using Iterator = std::vector<int>::const_iterator;
    using Elem = std::pair<Iterator, Iterator>;
    std::priority_queue<Elem, std::vector<Elem>, Comp> pq;
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    for (const auto& ns : nums) {
      if (ns.size() == 0) continue;
      if (min > *ns.cbegin()) min = *ns.cbegin();
      if (max < *ns.cbegin()) max = *ns.cbegin();
      pq.emplace(ns.cbegin(), ns.cend());
    }

    std::cout << min << ' ' << max << '\n';
    std::cout << *(pq.top().first) << '\n';

    if (pq.size() == 1) return {min, max};
    // int localMin = min;
    int localMax = max;

    while (true) {
      auto smallNext = pq.top();
      pq.pop();
      // exhausted, no better exists
      ++(smallNext.first);
      if (smallNext.first == smallNext.second) break;
      int potentialMax = *(smallNext.first);
      pq.push(smallNext);

      int currentMin = *(pq.top().first);
      // check boundary if it needs update
      if (potentialMax > localMax)
        localMax = potentialMax;

      // if it reduce the gap
      if (localMax - currentMin < max - min) {
        max = localMax;
        min = currentMin;
      }
    }
    return {min, max};
  }
};
