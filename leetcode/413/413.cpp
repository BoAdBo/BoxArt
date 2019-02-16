class Solution {
public:
  int numberOfArithmeticSlices(vector<int>& A) {
    // all consecutive arithmetics
    return numberOfArithmeticSlices(A.cbegin(), A.cend());
  }


  // self
  template <typename Iterator>
  int numberOfArithmeticSlices(Iterator first, Iterator last) {
    if (std::distance(first, last) < 3) return 0;
    if (first == last) return 0;
    int count = 0;
    int length = 0;

    Iterator mid = first+1;
    Iterator right = mid+1;
    for (; right != last;
         ++first, ++mid, ++right) {
      if (*mid - *first == *right - *mid) {
        ++length;
      }
      else {
        if (length > 0) {
          // (n-1)(n-2)/2, n = length+2
          count += length * (length + 1) / 2;
          length = 0;
        }
      }
    }

    if (length > 0)
      count += length * (length + 1) / 2;

    return count;
  }
};
