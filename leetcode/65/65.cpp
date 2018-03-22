#include <string>
#include <iostream>
#include <cassert>
#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"

using std::string;
using std::cout;

class Solution1 {
public:
  bool isNumber(string s) {
    // preprocess trim off spaces from start and back
    string trim_s = trim(s);

    /*
      locate - or e
     */
    if(trim_s[0] == '-') {
      trim_s = trim_s.substr(1, trim_s.size()-1);
    }
    unsigned int i;
    while(i < trim_s.size() && trim_s[i] != 'e') {
      i++;
    }

    if (i == trim_s.size()) {
      return seq_number(trim_s.substr(0, i));
    }

    return seq_number(trim_s.substr(0, i)) &&
      seq_number(trim_s.substr(i+1, trim_s.size() - i - 1));
  }

  /*
    Trim off spaces from start and back
   */
  string trim(string &sp) {
    unsigned int i = 0;
    while(sp[i] == ' ' && i < sp.size()) {
      i++;
    }

    unsigned int j = sp.size()-1;
    while(sp[j] == ' ' && j > 0) {
      j--;
    }

    // if all spaces, i,j would overlap
    return sp.substr(i, j-i+1);
  }

  /*
    Return True if all characters in s in digits [0-9]
  */
  bool seq_number(string s) {
    for(unsigned int i = 0; i < s.size(); ++ i) {
      if(s[i] > '9' || s[i] < '0') {
        return false;
      }
    }
    if(s.size() > 0) {
      return true;
    }
    return false;
  }
};


class Solution : public Solution1 {
};

TEST_GROUP(Solution) {
  Solution* sol;

  void setup() {
    sol = new Solution();
  }

  void teardown() {
    delete sol;
  }
};

TEST(Solution, seq_number_check) {
  CHECK(sol->seq_number("1"));
  CHECK_FALSE(sol->seq_number(" 1 "));
  CHECK_FALSE(sol->seq_number("1 1"));
  CHECK_FALSE(sol->seq_number("s"));
}

TEST(Solution, isNumber_check) {
  CHECK(sol->isNumber("1e10"));
  CHECK(sol->isNumber("-10"));
  CHECK(sol->isNumber("10.100"));
  CHECK(sol->isNumber("10.1"));
  CHECK_FALSE(sol->isNumber("-1-"));
  CHECK_FALSE(sol->isNumber("-1e"));
  CHECK_FALSE(sol->isNumber("10000 000"));
}

#include "CppUTest/CommandLineTestRunner.h"

int main(int argc, char* argv[]) {
  // Solution test;
  // string s = "  1111  ";
  // cout << test.trim(s) << std::endl;
  return CommandLineTestRunner::RunAllTests(argc, argv);
}
