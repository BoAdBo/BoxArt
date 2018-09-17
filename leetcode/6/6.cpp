class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows == 1) return s;
    int T = 2 * numRows - 2;
    std::vector<std::string> target(numRows);

    // can be improved by removing %
    // expand it into two loops
    for (int i = 0; i < s.size(); ++ i) {
      int row = i % T;
      if (row >= numRows)
        row = T - row;
      target[row].push_back(s[i]);
    }

    std::string result;
    for (const auto &str : target) {
      result.append(str);
    }
    return result;
  }
};
