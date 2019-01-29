static const int accelerate = []() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class NumArray {
  std::vector<int> m_nums;
public:
  // clear all bits except the lowest
  template <typename Integral>
  Integral LSB(Integral i) const {
    return i & (-i);
  }

  NumArray(vector<int> nums) : m_nums(nums.size()+1) {
    std::copy(nums.begin(), nums.end(), std::next(m_nums.begin()));
    for (std::size_t i = 1; i < m_nums.size(); ++i) {
      auto j = i + LSB(i);
      if (j < m_nums.size()) {
        m_nums[j] += m_nums[i];
      }
    }
  }

  void add(int i, int val) {
    // we assume no OF
    while (i < m_nums.size())
      m_nums[i] += val, i += LSB(i);
  }

  void update(int i, int val) {
    int oldVal = sumRange(i, i);
    add(i+1, val-oldVal);
  }

  int sumToIndex(int i) const {
    int sum = 0;
    while (i > 0)
      sum += m_nums[i], i -= LSB(i);
    return sum;
  }

  int sumRange(int i, int j) const {
    return sumToIndex(j+1) - sumToIndex(i);
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
