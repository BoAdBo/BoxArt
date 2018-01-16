class Solution {
 public:
  bool check(int x, int remain) {
    int digit = remain % 10;
    if(digit == 0) {
      return false;
    }
    else { // recursive calls until
      return (x % digit == 0) && (remain / 10 == 0 || check(x, remain/10));
    }
  }
  vector<int> selfDividingNumbers(int left, int right) {
    vector<int> rs; // result set
    for(int i = left; i <= right; ++ i) {
      if(check(i, i)) {
        rs.push_back(i);
      }
    }
    return rs;
  }
};
