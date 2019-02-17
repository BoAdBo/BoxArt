class Solution {
public:
  int numberOfArithmeticSlices(vector<int>& A) {
    return numberOfArithmeticSlices(A.cbegin(), A.cend());
  }

  template <typename Iterator>
  int numberOfArithmeticSlices(Iterator first, Iterator last) {
    const int n = std::distance(first, last);
    if (n < 3) return 0;
    int count = 0;
    // the number of arithmetic weak subsequence ending with A[i]
    std::vector<std::unordered_map<long, int>> dp(n);
    for (Iterator i = first+1; i != last; ++i) {
      for (Iterator j = first; j != i; ++j) {
        const long delta = static_cast<long>(*i) - static_cast<long>(*j);
        dp[i - first][delta] += (dp[j - first][delta] + 1);
        // count += (dp[j - first][delta] + 1);
        count += dp[j - first][delta];
      }
    }

    // return count - n * (n-1) / 2;
    return count;
  }

  template <typename Iterator>
  int numberOfArithmeticSlices(Iterator first, Iterator last) {
    const int n = std::distance(first, last);
    if (n < 3) return 0;
    // the number of arithmetic subsequence ending with A[i]
    std::vector<int> dp(n, 0);
    std::vector<std::unordered_set<int>> deltas(n-1, 0);
    // build deltas
    for (Iterator i = first+1; i != last; ++i) {
      for (Iterator j = first; j != i; ++ j) {
        deltas[i - first - 1].insert(*i - *j);
      }
    }

    // Iterator mid = first + 1;
    // Iterator right = mid + 1;
    for (int i = 0; i < n; ++ i) {
      for (int j = 0; j < i; ++ j) {
        if (deltas)
        dp[i]
      }
    }
  }
};
