struct comp {
  bool operator() (const std::tuple<int, int, int>& a,
                   const std::tuple<int, int, int>& b) {
    return std::get<0>(a) < std::get<0>(b);
  }
};

class Solution {
 public:
  int threeSumClosest(vector<int>& nums, int target) {
    std::vector<std::tuple<int, int, int>> twoSums;
    for (int i = 0; i < nums.size(); ++ i) {
      for (int j = i + 1; j < nums.size(); ++ j) {
        twoSums.emplace_back(nums[i] + nums[j], i, j);
      }
    }

    std::sort(twoSums.begin(), twoSums.end(), comp());
    int min = std::numeric_limits<int>::max();
    int res = std::numeric_limits<int>::max();

    for (int k = 0; k < nums.size(); ++ k) {
      // find the first element not smaller, then the candidate is either itself
      // or its former
      const auto val = target - nums[k];
      auto iter = std::lower_bound(twoSums.cbegin(), twoSums.cend(),
                                   std::make_tuple(val, 0, 0), comp());
      if (iter != std::cend(twoSums) &&
          (std::get<1>(*iter) == k || std::get<2>(*iter) == k))
        continue;

      if (iter == std::cend(twoSums)) {
        if (std::get<1>(twoSums.back()) == k ||
            std::get<2>(twoSums.back()) == k)
          continue;
        if (min > std::abs(val - std::get<0>(twoSums.back()))) {
          min = std::abs(val - std::get<0>(twoSums.back()));
          res = std::get<0>(twoSums.back()) + nums[k];
        }
      }
      else if (iter == std::cbegin(twoSums)) {
        if (min > std::abs(val - std::get<0>(*iter))) {
          min = std::abs(val - std::get<0>(*iter));
          res = std::get<0>(*iter) + nums[k];
        }
      } else {
        if (min > std::abs(val - std::get<0>(*iter))) {
          min = std::abs(val - std::get<0>(*iter));
          res = std::get<0>(*iter) + nums[k];
        }
        if (min > std::abs(val - std::get<0>(*(iter - 1)))) {
          min = std::abs(val - std::get<0>(*(iter - 1)));
          res = std::get<0>(*(iter - 1)) + nums[k];
        }
      }
    }
    return res;
  }
};
