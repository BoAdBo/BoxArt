// memorization
class Solution {
public:
  int findTargetSumWays(vector<int>& nums, int S) {
    if (nums.size() == 0) return 0;

    std::vector<int> postfixSum(nums.size(), 0);
    std::vector<std::vector<int>> memo(nums.size(),
                                       std::vector<int>(2001, -1));
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
                    postfixSum.cbegin(), memo.begin(), S);
    else return 0;
  }

  template <typename Iterator, typename ConstIterator>
  int helper(ConstIterator first, ConstIterator last,
             ConstIterator firstPost, Iterator firstMemo, int target) {
    if (first == last) return (target == 0);
    if ((*firstMemo)[target + 1000] != -1) return (*firstMemo)[target + 1000];
    int matchNum = 0;
    int nextTarget = 0;
    // addition operator, check range
    nextTarget = target - *first;
    if (nextTarget <= *firstPost && nextTarget >= -(*firstPost))
      matchNum = helper(first+1, last, firstPost+1, firstMemo+1, nextTarget);

    // minus operator, check range
    nextTarget = target + *first;
    if (nextTarget <= *firstPost && nextTarget >= -(*firstPost))
      matchNum += helper(first+1, last, firstPost+1, firstMemo+1, nextTarget);
    (*firstMemo)[target + 1000] = matchNum;
    return matchNum;
  }
};
