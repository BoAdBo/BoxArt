#include "predefined.hpp"

class Solution {
public:
  vector<vector<int>> generate(int numRows) {
    if (numRows == 0) return vector<vector<int>>();
    if (numRows == 1) return vector<vector<int>>(1, vector<int>(1, 1));
    else {
      vector<vector<int>> pre = generate(numRows - 1);
      //auto t = generate(numRows - 1);
      vector<int> tmp;
      for (int i = 0; i < numRows; ++ i) {
        // numRows -> numRows - 1 as previous
        // numRows-1 -> numRows - 2 as starting from 0
        int pos = numRows-2;
        int left = i-1, right = i;
        if(left < 0) left = 0;
        else left = pre[pos][left];
        if(right > pos) right = 0;
        else right = pre[pos][right];
        tmp.emplace_back(left + right);
      }
      pre.emplace_back(move(tmp));
      return pre;
    }
  }
};
