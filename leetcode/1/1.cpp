class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    std::unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++ i) {
      m[target - nums[i]] = i;
    }
    for (int i = 0; i < nums.size(); ++ i) {
      std::unordered_map<int, int>::const_iterator iter = m.find(nums[i]);
      if (iter != m.end() && iter->second != i) {
        return {iter->second, i};
      }
    }
    return {-1, -1};
  }

  vector<int> twoSum(vector<int>& nums, int target) {
    std::unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++ i) {
      std::unordered_map<int, int>::const_iterator iter = m.find(target - nums[i]);
      if (iter != m.end()) {
        return {iter->second, i};
      }
      else {
        m[nums[i]] = i;
      }
    }
    return {-1, -1};
  }

  vector<int> twoSum(vector<int>& nums, int target) {
    std::vector<int> old(nums);
    std::sort(nums.begin(), nums.end());
    int i = 0, j = nums.size() - 1;
    for (; i != j; ) {
      const auto curr = nums[i] + nums[j];
      if (target < curr) {
        --j;
      }
      else if (target > curr) {
        ++i;
      }
      else {
        // i == j would exit, not entering here
        // target == curr
        break;
      }
    }

    std::vector<int> res;
    for (int p = 0; p < old.size(); ++ p) {
      if (old[p] == nums[i] || old[p] == nums[j]) res.push_back(p);

      if (res.size() == 2) return res;
    }
    return {-1, -1};
  }
};
