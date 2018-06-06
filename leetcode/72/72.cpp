class Solution {
public:
  int minDistance(string word1, string word2) {

    auto n = word1.size(), m = word2.size();
    // array for dynamic programming
    // word1.size() == n, word2.size() == m
    // dp [i][j] defined as convert word1[0..i] to word2[0..j] s.t. i < n, j < m
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // boundary case
    for ( auto i = 0u; i <= n; ++ i ) {
      // Convert word1[0..i] to word2[0] which is an empty string
      // delete all, requires i operations
      dp[i][0] = i;
    }

    for ( auto i = 0u; i <= m; ++ i ) {
      // same, but inserting i characters
      dp[0][i] = i;
    }

    // general case
    // Assume we have the minimum steps of operations to convert
    // word1[0..i-1] => word2[0..j-1], aka dp[i]
    // ============================================================
    // so for word[0..i] => word2[0..j]
    // if word1[i] == word2[j], there is no operation required
    // dp[i][j] = dp[i-1][j-1]
    // else consider three operations
    // ============================================================
    // Delete: if word1[0..i-1] == word2[0..j]
    // NOTE: before we are claiming that we have the minimum steps to convert
    // word1[0..i-1] not necessarily equal to word2[0..j-1]
    // so dp[i][j] = dp[i-1][j] + 1 (if perform delete)
    // ============================================================
    // Insert: if word1[0..i] + word2[j] == word2[0..j]
    // word1[0..i] == word2[0..j-1]
    // dp[i][j] = dp[i][j-1] + 1
    // ============================================================
    // Replace: if word1[0..i-1] + word2[j] == word2[0..j]
    // word1[0..i-1] == word2[0..j-1]
    // dp[i][j] = dp[i-1][j-1] + 1

    // so the iteration would start from
    for ( auto i = 1u; i <= n; ++ i ) {
      for ( auto j = 1u; j <= m; ++ j ) {
        if ( word1[i - 1] == word2[j - 1] ) {
          dp[i][j] = dp[i-1][j-1];
        }
        else {
          // dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + 1});
          //dp[i][j] = 1 + min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]);//min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
          dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
      }
    }

    return dp[n][m];
  }
};
