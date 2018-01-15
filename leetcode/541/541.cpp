#include <string>
#include <stack>
#include <iostream>
#include <stdio.h>
using std::cout;
using std::stack;
using std::string;

class Solution {
private:
  string reverse(string s) {
    stack<char> stk;
    //cout << s << "\n";
    for(int i = 0; i < s.size(); ++i) {
      stk.push(s[i]);
    }
    string first = "";
    while(!stk.empty()) {
      first += stk.top();
      stk.pop();
    }

    return first;
  }
public:
  string reverseStr(string s, int k) {
    if((int)s.size() < k) {
      return reverse(s);
    }
    else if((int)s.size() >= 2 * k) {
      return reverse(s.substr(0, k)) + s.substr(k, k) +
        reverseStr(s.substr(2*k, s.size()-2*k), k);
    }
    else {
      return reverse(s.substr(0, k)) + ((int)s.size() > k ? s.substr(k, s.size()-k) : "");
    }
  }
};


int main() {
  Solution test;
  //printf("%s", test.reverseStr("abcdefg", 2));
  //cout << ((string)"abs").substr(0,3) << "\n";
  cout << test.reverseStr("abcdefg", 2);
}
