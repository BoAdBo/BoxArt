class Solution {
public:
  vector<string> removeInvalidParentheses(string s) {
    static std::string expr;
    static std::unordered_set<std::string> res_set;
    int min_count = std::numeric_limits<int>::max();
    helper(s, expr, 0, 0, 0, min_count, res_set);
    std::vector<string> res(res_set.cbegin(), res_set.cend());
    res_set.clear();
    expr.clear();
    return res;
  }

  void helper(const string& s, string& expr, int i, int left, int right, int& min_count, std::unordered_set<std::string>& res) {
    if (i == s.size()) {
      if (left == right) {
        const int rem_count = s.size() - expr.size();
        if (rem_count <= min_count) {
          if (rem_count < min_count) {
            res.clear();
            min_count = rem_count;
          }
          res.insert(expr);
        }
      }
    }
    else {
      if (s[i] != '(' && s[i] != ')') {
        expr.push_back(s[i]);
        helper(s, expr, i + 1, left, right, min_count, res);
        expr.pop_back();
      }
      else {
        // contains
        if (s[i] == '(') {
          expr.push_back(s[i]);
          helper(s, expr, i + 1, left + 1, right, min_count, res);
          expr.pop_back();
        }
        else {
          if (left > right) {
            expr.push_back(s[i]);
            helper(s, expr, i + 1, left, right + 1, min_count, res);
            expr.pop_back();
          }
        }
        // discards
        helper(s, expr, i + 1, left, right, min_count, res);
      }
    }
  }
};

class Solution {
public:
  vector<string> removeInvalidParentheses(string s) {

  }

};
