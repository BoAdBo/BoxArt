class Solution {
 public:
  int firstMissingPositive(vector<int>& nums) {
    const int n = nums.size();
    // The for loops guarantees, every within bound number will take its correct
    // place in the array
    for (int i = 0; i < n; ) {
      // Within bound, or nums to be swapped is not at the correct position, due
      // to duplication, need to add here
      if (nums[i] > 0 && nums[i] <= n &&
          nums[nums[i] - 1] != nums[i]) {
        std::swap(nums[i], nums[nums[i] - 1]);
        // pass only if it's at the corrent pos or two elements are duplicated
        if (nums[i] - 1 == i) ++i;
      }
      else ++i;
    } // every pass means that the num is at the correct position or its correct
      // position is already taken, or it's an out of bound number, whose
      // position we don't care.

    for (int i = 0; i < n; ++i)
      if (nums[i] - 1 != i) return i + 1;
    // default to the size + 1
    return nums.size() + 1;
  }
};
