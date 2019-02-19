class Solution {
public:
  void nextPermutation(vector<int>& nums) {
    // nextPermutation(nums.begin(), nums.end());
    my_next_permutation(nums.begin(), nums.end(), std::less<int>());
  }

  template <typename Iterator>
  bool nextPermutation(Iterator first, Iterator last) {
    if (first == last) return false;
    Iterator i = last;
    if (first == --i) return false;

    while (true) {
      Iterator i1 = i;
      if (*--i < *i1) {
        Iterator i2 = last;
        while (!(*--i2 > *i)) ;

        std::iter_swap(i, i2);
        std::reverse(i1, last);
        return true;
      }
      if (i == first) {
        std::reverse(first, last);
        return false;
      }
    }
  }
  template <typename I, typename C>
  // requires BidirectionalIterator<I> && Compare<C>
  bool my_next_permutation(I begin, I end, C comp) {
    auto rbegin = std::make_reverse_iterator(end);
    auto rend = std::make_reverse_iterator(begin);
    auto next_unsorted = std::is_sorted_until(rbegin, rend, comp);
    bool at_final_permutation = (next_unsorted == rend);
    if (!at_final_permutation) {
      auto next_permutation = std::upper_bound(
        rbegin, next_unsorted, *next_unsorted, comp);
      std::iter_swap(next_unsorted, next_permutation);
    }
    std::reverse(rbegin, next_unsorted);
    return !at_final_permutation;
  }

  template <typename I, typename C>
  bool next_permutation(I first, I last, C comp) {
    auto rfirst = std::make_reverse_iterator(last);
    auto rlast = std::make_reverse_iterator(first);
    auto next_unsorted = std::sorted_until(rfirst, rlast, comp);
    bool at_final_permutation = (next_unsorted == rlast);
    if (!at_final_permutation) {
      auto next = std::upper_bound(rfirst, rlast, *next_unsorted);
      std::iter_swap(next, at_final_permutation);
    }
    std::reverse(rfirst, next_unsorted);
    return !at_final_permutation;
  }
};

// my ugly version
class Solution {
public:
  void nextPermutation(vector<int>& nums) {
    // nextPermutation(nums.begin(), nums.end());
    std::next_permutation(nums.begin(), nums.end());
  }

  template <typename Iterator>
  bool nextPermutation(Iterator first, Iterator last) {
    if (first == last) return false;
    Iterator i = last-1;
    if (first == i) return false;

    Iterator i1 = last-1;
    --i;
    while (*i >= *i1 && i != first) {
      --i; --i1;
    }

    if (*i < *i1) {
      Iterator i2 = last-1;
      while (*i2 <= *i && i2 != first) {
        --i2;
      }
      std::iter_swap(i, i2);
      std::reverse(i1, last);
      return true;
    }
    else {
      std::reverse(i, last);
      return true;
    }
  }
};
