#include "predefined.hpp"
#define PIVOT_POS 0

// class Solution {
// public:
//   int findKthLargest(vector<int>& nums, int k) {
//     // assume k is no larger than nums.size()
//     partial_sort(nums, 0, nums.size() - 1, k-1);
//     return nums[k-1];
//   }

//   // sort elements size of (right - left + 1)
//   // to have (left, last) elements sorted
//   void partial_sort(vector<int> & nums, int left, int right, int last) {
//     if (left < right) {
//       int _pivot_pos = left + PIVOT_POS;
//       const int pivot = nums[_pivot_pos];

//       // swap to first
//       swap(nums[_pivot_pos], nums[left]);
//       // the pointer of current pivot, elements before are smaller
//       _pivot_pos = left;

//       for( int i = left + 1; i <= right; ++ i ) {
//         if( nums[i] > pivot ) {
//           swap(nums[++_pivot_pos], nums[i]);
//         }
//       }
//       swap(nums[_pivot_pos], nums[left]);

//       if ( _pivot_pos == last ) {
//         if ( _pivot_pos > left ) {
//           sort(&nums[left], &nums[_pivot_pos], greater<int>());
//         }
//       }
//       else if ( _pivot_pos < last ) {
//         // call quicksort to complete left
//         // partial_sort for (_pivot_pos+1,right, last)
//         if ( _pivot_pos > left ) {
//           sort(&nums[left], &nums[_pivot_pos], greater<int>());
//         }
//         partial_sort(nums, _pivot_pos + 1, right, last);
//       }
//       else {
//         partial_sort(nums, left, _pivot_pos - 1, last);
//       }
//     }
//   }
// };

class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) {
    return nums[__nth_element(nums, 0, nums.size()-1, k-1)];
  }

private:
  static int __nth_element(vector<int> &nums, int left, int right, int k) {
    if (left == right) return left;
    if (left < right) {
      // with a little tweak of pivot position, we can avoid performance hit from the test set
      int _pivot_pos = (left + right) / 2;
      const int pivot = nums[_pivot_pos];

      // swap to first
      swap(nums[_pivot_pos], nums[left]);
      // the pointer of current pivot, elements before are smaller
      _pivot_pos = left;

      for( int i = left + 1; i <= right; ++ i ) {
        if( nums[i] > pivot ) {
          swap(nums[++_pivot_pos], nums[i]);
        }
      }
      swap(nums[_pivot_pos], nums[left]);

      if ( k == _pivot_pos ) {
        return _pivot_pos;
      }
      else if ( k < _pivot_pos ){
        return __nth_element(nums, left, _pivot_pos-1, k);
      }
      else {
        return __nth_element(nums, _pivot_pos+1, right, k);
      }
    }

  }
};
