class Solution {
public:
  int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    // avoid overflow

    while (left < right) {
      auto mid = left + (right - left) / 2;
      if (nums[mid] < target) {
        left = mid+1;
      } else {
        right = mid;
      }
    }
    return nums[right] == target ? right : -1;
  }

  template <typename Iterator>
  int search(Iterator first, Iterator last, int target) {
    while (first != last) {
      auto mid = first + (last - first) / 2;

      if (*mid < target) first = mid+1;
      else last = mid;
    }
    return first;
  }
};
