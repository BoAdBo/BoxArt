#include "predefined.hpp"

class Solution {
public:
  string nearestPalindromic(string n) {
    // basic idea is to flip.
    if (n == "11") {
      return "9";
    }
    if(n[0] == '1' && n.size() > 1) {
      int i = 1;
      while(n[i] == '0' && i < n.size()) {
        i++;
      }
      if (i == n.size()) {
        // all zero with a starting '1'
        return string(n.size()-1, '9');
      }
    }

    int shift = n.size() / 2;
    if(n.size() % 2 == 0) {
      shift--;
    }

    string left, center, right;
    int    d1,   d2,     d3;
    left = right = center = n;
    if(n[shift] == '0') {

      right[shift] += 1;

      // not possible for all 0
      while(left[shift] == '0') {
        left[shift] = '9';
        shift--;
      }

      left[shift] -= 1;

      if(left[shift] == '0' && shift == 0) {
        // remove the zero from the top
        left.erase(0, 1);
      }

    }
    else if(n[shift] == '9') {
      left[shift] -= 1;

      // could be putting a new number
      while(right[shift] == '9' && shift>= 0) {
        right[shift] = '0';
        shift--;
      }

      if(shift < 0) {
        right.insert(0, "1");
      }
      else {
        right[shift] += 1;
      }

    }
    else {

      left[shift] -= 1;
      right[shift] += 1;

    }

    _fliped(left);
    _fliped(center);
    _fliped(right);
    //cout << left << " " << center << " " << right << endl;

    d1 = distance_str(n, left);
    d2 = distance_str(n, center);
    d3 = distance_str(n, right);
    //cout << d1 << " " << d2 << " " << d3 << endl;
    if(center == n) {
      return d1 <= d3 ? left : right;
    }

    if(d1 <= d2) {
      if(d1 <= d3) {
        return left;
      }
      else {
        return right;
      }
    }
    else {
      if(d2 <= d3) {
        return center;
      }
      else {
        return right;
      }
    }

  }

private:
  int _fliped(string& n) {

    for (int i = 0, j = n.size() - 1; i < n.size() / 2; ++ i, -- j) {
      n[j] = n[i];
    }

    return 0;
  }

  int distance_str(const string & a, const string &b) {
    //cout << a << endl << b << endl;
    int distance = 0;
    int base = 1;
    // at most 1 shift of base 10
    if (a.size() > b.size()) {
      distance -= pow(10, a.size() - 1);
    }
    else if(a.size() < b.size()){
      distance += pow(10, b.size() - 1);
    }

    for (int i = a.size()-1, j = b.size()-1; j >= 0 && i >= 0; -- i, --j) {
      distance += ((b[j] - a[i]) * base);
      base *= 10;
    }
    return abs(distance);
  }
};
