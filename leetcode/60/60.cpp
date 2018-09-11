class Solution {
public:
  string getPermutation(int n, int k) {
    std::vector<int> factorial_num(n-1, 1);
    std::vector<int> index_array(n, 0);
    std::vector<bool> picked(n, false);
    std::string res;
    for (int i = 1; i < factorial_num.size(); ++ i)
      factorial_num[i] = (i + 1) * factorial_num[i-1];

    int index = k-1;
    for (int i = factorial_num.size()-1, j = 0;
         i >= 0; -- i, ++ j) {
      index_array[j] = index / factorial_num[i];
      index = index % factorial_num[i];
    }

    for (const auto & item : index_array) {
      int i = 0;
      int step = 0;
      // find the first to iterate
      while (picked[step] && step < picked.size())
        {++step; }

      while (i < item && step < picked.size()) {
        ++step;
        if (!picked[step])
          ++i;
      }
      picked[step] = true;
      res += static_cast<char>(step + '1');
    }

    return res;
  }
};
