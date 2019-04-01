class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // since nums1.size() > 0 && nums2.size() > 0, therefore totalSize > 1
    const std::size_t totalSize = nums1.size() + nums2.size();
    // current count of number, we want to find totalSize/2-1
    std::size_t currentCount = 0;
    std::size_t i = 0, j = 0;
    double mid = std::numeric_limits<double>::max();
    double next = std::numeric_limits<double>::max();
    while (i < nums1.size() && j < nums2.size() &&
           currentCount < totalSize / 2) {
      if (nums1[i] <= nums2[j]) {
        mid = nums1[i];
        ++i;
      } else {
        mid = nums2[j];
        ++j;
      }
      ++currentCount;
    }

    while (i < nums1.size() && currentCount < totalSize / 2) {
      mid = nums1[i];
      ++i;
      ++currentCount;
    }
    while (j < nums2.size() && currentCount < totalSize / 2) {
      mid = nums2[j];
      ++j;
      ++currentCount;
    }

    assert(i < nums1.size() || j < nums2.size());
    if (i < nums1.size() && j < nums2.size()) {
      next = nums1[i] <= nums2[j] ? nums1[i] : nums2[j];
    } else if (i < nums1.size()) {
      next = nums1[i];
    } else {
      next = nums2[j];
    }
    if (totalSize % 2 == 0) return (mid + next) / 2;
    else return next;
  }
};
