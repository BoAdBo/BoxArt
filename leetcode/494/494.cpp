class Solution {
public:
  int findTargetSumWays(vector<int>& nums, int S) {
    if (nums.size() == 0) return 0;

    std::vector<int> postfixSum(nums.size(), 0);
    int sum = 0;
    for (int i = 0; i < nums.size(); ++ i) {
      postfixSum[i] = sum + nums[i];
      sum += nums[i];
    }
    for (int& n : postfixSum) {
      n = sum - n;
    }

    if (S <= sum && S >= -sum)
      return helper(nums.cbegin(), nums.cend(),
                    postfixSum.cbegin(), postfixSum.cend(),  S);
    else return 0;
  }

  template <typename Iterator>
  int helper(Iterator first, Iterator last,
             Iterator firstPost, Iterator lastPost, int target) {
    if (first == last) return (target == 0);
    int matchNum = 0;
    int nextTarget = 0;
    // addition operator, check range
    nextTarget = target - *first;
    if (nextTarget <= *firstPost && nextTarget >= -(*firstPost))
      matchNum = helper(first+1, last, firstPost+1, lastPost, nextTarget);

    // minus operator, check range
    nextTarget = target + *first;
    if (nextTarget <= *firstPost && nextTarget >= -(*firstPost))
      matchNum += helper(first+1, last, firstPost+1, lastPost, nextTarget);
    return matchNum;
  }
};
