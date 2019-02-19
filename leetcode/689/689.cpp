class Solution {
public:
  vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    std::vector<int> res = {0, k, 2*k};
    // two vector to store the left and right best candidates
    // one vector to store the W, where W[i] is the sum of nums[i:i+k]
    const int size = nums.size() - k + 1;
    std::vector<int> W(size, 0);

    for (int j = 0; j < k; ++ j)
      W[0] += nums[j];

    for (int i = 1; i < size; ++ i)
      W[i] = W[i-1] - nums[i-1] + nums[i+k-1];

    // largest of W in range [0, i+1)
    std::vector<int> dpLeft(size - 2*k, 0);
    // largest of W in range [size-i-1, size)
    std::vector<int> dpRight(size - 2*k, size - 1);

    int max = W[0];
    // may need to consider equal
    for (int i = 1; i < dpLeft.size(); ++ i)
      if (max < W[i]) {
        dpLeft[i] = i;
        max = W[i];
      }
      else
        dpLeft[i] = dpLeft[i-1];

    max = W[size-1];
    for (int i = 1; i < dpRight.size(); ++ i)
      // size-i <=> i-1, size-i-1 <=> i
      if (max < W[size-i-1]) {
        dpRight[i] = size-i-1;
        max = W[size-i-1];
      }
      else
        dpRight[i] = dpRight[i-1];

    // i + k <= j, i \in [0, j-k+1)
    // j + k <= p, p \in [j+k, size)
    // k \in [k, size-k)
    for (int j = k; j < size - k; ++ j) {
      // find the largest [0, j-k+1) from left, j-k+1 == i+1
      const int left = dpLeft[j-k];
      // find the largest [j+k, size) from right, j+k == size-i-1
      const int right = dpRight[size-j-k-1];
      const int mid = j;

      const int sum = W[left] + W[mid] + W[right];
      if (sum > W[res[0]] + W[res[1]] + W[res[2]]) {
        res[0] = left;
        res[1] = mid;
        res[2] = right;
      }
    }

    return res;
  }
};
