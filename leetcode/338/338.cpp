
#include <vector>
using std::vector;

class Solution1 {
public:
  static int bits(int num) {
    if(num == 0) return 0;
    else {
      return (num % 2) + bits(num >> 1);
    }
  }

  vector<int> countBits(int num) {
    vector<int> res;
    for(int i = 0; i <= num; ++i) {
      res.push_back(bits(i));
    }

    return res;
  }
};

class Solution2 {
  vector<int> mem;
public:
  int bits(int num) {
    if(mem[num] == -1) {
      int res = 0;
      if(num == 0) {
        res = 0;
      }
      else {
        res = (num % 2) + bits(num >> 1);
      }
      mem[num] = res;
      return mem[num];
    }
    else {
      return mem[num];
    }
  }

  vector<int> countBits(int num) {
    mem = vector<int>(num+1,-1);

    vector<int> res;
    for(int i = 0; i <= num; ++i) {
      res.push_back(bits(i));
    }

    return res;
  }
};

class Solution : public Solution2{

};

#include <iostream>
using std::cout;

int main() {
  //cout << (1 << 2);
  // Solution1 test1;
  // test1.countBits(100000000);

  // Solution2 test2;
  // test2.countBits(100000000);
}
