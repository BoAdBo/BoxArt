#include <iostream>
#include <limits.h>

using std::string;
using std::cout;

class Solution {
public:
  int longestPalindromeSubseq(string s) {
    int max = INT_MIN;
    for(int i = 0; i < s.size(); ++ i) {
      if(s.size() > 1 && s[i] == s[i+1]) {
        int length = 0;
        int left = i-length-1;
        int right = (i+1)+length+1;

        while(left >= 0 && right < s.size() &&
              s[left] == s[right]) {
          length++;
          left = i - length-1;
          right = i + length+1;
        }
        length = 2*(length+1);
        if(length > max) {
          max = length;
        }
      }
      {
        int length = 0;
        int left = i-length-1;
        int right = i+length+1;

        while(left >= 0 && right < s.size() &&
              s[left] == s[right]) {
          length++;
          left = i - length-1;
          right = i + length+1;
        }

        length = 2*length + 1;
        if(length > max) {
          max = length;
        }
      }
    }
    return max;
  }
};

int main() {
  Solution test;
  cout << test.longestPalindromeSubseq("aaaabbbb");
}
