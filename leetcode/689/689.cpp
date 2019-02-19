// my ugly version
class Solution {
public:
  vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    // store result
    std::vector<int> res = {0, k, 2*k};
    // two vector to store the left and right best candidates
    // largest of W in range [0, i+1)
    std::vector<int> dpLeft(size - 2*k, 0);
    // largest of W in range [size-i-1, size)
    std::vector<int> dpRight(size - 2*k, size - 1);
    // one vector to store the W, where W[i] is the sum of nums[i:i+k]
    std::vector<int> W(size, 0);
    const int size = nums.size() - k + 1;

    for (int j = 0; j < k; ++ j)
      W[0] += nums[j];

    for (int i = 1; i < size; ++ i)
      W[i] = W[i-1] - nums[i-1] + nums[i+k-1];

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

// one of the best version
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& a, int k) {
        int n = a.size();
        vector<int>  c[3],m(3); //store optimal solutions for 1 sum, 2 sums, 3 sums.
        int left = 0, mid = 0, right = 0;
        vector<int> b(n);
        int sm = 0;
        for (int i = 0; i < n; ++i) {
            sm += a[i];
            if (i >=k-1) {
                b[i] = sm;
                sm -= a[i-k+1];
                if (i >= 3 * k-1) {
                    if (b[i-k-k] > m[0]) { // update 1 sum solution
                        m[0] = b[i-k-k];
                        left = i - k - k;
                        c[0] = {i-k-k};
                    }
                    if (b[i-k] + m[0] > m[1]) { // update 2 sums solution
                        m[1] = b[i-k] + m[0];
                        mid = i - k;
                        c[1] = {c[0][0], i-k};
                    }
                    if (b[i] + m[1] > m[2]) { //update 3 sums solution
                        m[2] = m[1] + b[i];
                        c[2] = {c[1][0], c[1][1], i};
                        right = i;
                    }
                }
            }
        }
        return {c[2][0]-k + 1,c[2][1]-k+1,c[2][2]-k+1};
        //return {left-k + 1,mid-k+1,right-k+1};
    }
};
