class Solution1 {
public:
  static bool isPalindrome(int x) {
    // in case of x reaching the edge, making temp overflow
    if(x < 0) return false;
    long temp = 1;
    int count = 0;
    while(x / temp != 0) {
      temp*=10;
      count++;
    }

    int first = temp / 10; // the denominators to get the digit from start
    int last = 1;
    for(int i = 0; i < count / 2; ++ i) {
      int f_dig = (x / first) % 10;
      int l_dig = (x / last) % 10;
      if(f_dig != l_dig) {
        return false;
      }
      first/=10;
      last*=10;
    }
    return true;
  }
};

class Solution2 {
public:
  static bool isPalindrome(int x) {
    if(x < 0 || (x != 0 && x % 10 == 0)) return false;

    int revertedNumber = 0;
    while(x > revertedNumber) {
      // if x'last digits is 0 than, revertedNumber's first digit won't remember 0... therefore it needs to be excluded
      revertedNumber = revertedNumber * 10 + x % 10;
      x /= 10;
    }

    return x == revertedNumber || x == revertedNumber/10;
  }
};

class Solution : public Solution2{
};

#include <stdio.h>
#include <limits.h>
int main() {
  int temp;
  scanf("%d", &temp);
  if(Solution::isPalindrome(temp)) {
    printf("%s", "It is");
  }
  else {
    printf("it's not");
  }

  // for(int i = 0; i < INT_MAX; ++ i) {
  //   Solution::isPalindrome(i);
  // }
}
