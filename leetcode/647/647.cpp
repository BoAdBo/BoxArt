#include <string>
#include <iostream>
using std::cout;
using std::string;

class Solution1 {
public:
  static bool isPalindromeic(const string & s) {
    for(unsigned int i = 0; i <= (s.size()-1)/2; ++ i) {
      if(s[i] != s[s.size() - 1 - i]) {
        return false;
      }
    }
    return true;
  }

  int countSubstrings(string s) {
    // iterate through sub-string
    int count = 0;
    for(int i = 0; i < s.size(); ++ i) {
      for(int j = 1; j < s.size() - i + 1; ++ j) {
        if(isPalindromeic(s.substr(i,j))) count++;
      }
    }
    return count;
  }
};

/*
  The center could either be at the letter or in the middle of two letters

  that means that there are 2*N-1 position for center to be at
  ((1),(),(2)) if N=2 # center at => (1); between (1,2); and (2)
 */
class Solution2 {
public:
  int countSubstrings(string s) {
    int ans = 0;
    for(int center = 0; center < 2*s.size()-1; ++ center) {
      int left = center/2;
      int right = left + center % 2;
      while(left >= 0 && right < s.size() && (s[left] == s[right])) {
        ans++;
        left--;
        right++;
      }
    }
    return ans;
  }
};

class Solution : public Solution2{

};


int main() {
  //cout << Solution::isPalindromeic("abba") << "\n";
  Solution test;
  cout << test.countSubstrings("aaa") << "\n";
}
