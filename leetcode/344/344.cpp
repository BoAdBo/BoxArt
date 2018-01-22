class Solution {
public:
  string reverseString(string s) {
    stack<char> stk;
    for(int i = 0; i < s.size(); ++ i) {
      stk.push(s[i]);
    }
    string re = "";
    while(!stk.empty()) {
      re += stk.top();
      stk.pop();
    }
    return re;
  }
};
