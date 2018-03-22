#include "predefined.hpp"

class Solution {
public:
  string longestCommonPrefix(vector<string>& strs) {
    if (strs.size() == 0) return string();
    if (strs.size() == 1) return strs[0];
    else return _prefix_so_far(strs, 0);
  }

private:
  string _prefix_so_far(const vector<string> &strs, int prefix_size) {
    char tmp = strs[0][prefix_size];

    for ( int i = 1; i < strs.size(); ++ i ) {
      if ( prefix_size >= strs[i].size() || tmp != strs[i][prefix_size] ) {
        return "";
      }
    }

    return tmp + _prefix_so_far(strs, prefix_size+1);
  }

};
