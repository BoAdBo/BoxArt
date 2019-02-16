class Solution {
public:
  int numberOfArithmeticSlices(vector<int>& A) {

  }

  template <typename Iterator>
  int numberOfArithmeticSlices(Iterator first, Iterator last) {
    int n = std::distance(first, last);
    // the number of arithmetic subsequence ending with A[i]
    std::vector<int> dp(n, 0);
    std::vector<std::unordered_set<int>> deltas;

    dp[i]
  }
};
