class Solution {
 public:
  // either going left for j when larger, or going right for k when smaller
  // can be pruned out
  // consider the smaller case:
  // if k goes right, there exists a j' < j such that nums[j'] + nums[k+1] < target
  
  int threeSumClosest(vector<int>& nums, int target) {
    std::sort(nums.begin(), nums.end());
    int min = std::numeric_limits<int>::max();
    int res = std::numeric_limits<int>::max();
    for (int i = 0; i < nums.size(); ++ i) {
      int j = i + 1, k = nums.size() - 1;
      while (j < k) {
        auto sum = nums[i] + nums[j] + nums[k];
        if (sum < target) {
          ++j;
        } else {
          --k;
        }
      }
    }
  }
};
