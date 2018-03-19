#include "predefined.hpp"

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

class Solution {
public:
  /*
    A O(n^2) solution
   */
  map<tuple<int, int, int>, list<int> > hash_lines;

  int maxPoints(vector<Point>& points) {
    // if there were only a point
    if (points.size() == 1) return 1;

    // if there were the same point, it would fail
    for (int i = 0; i < points.size(); ++ i) {
      for (int j = i + 1; j < points.size(); ++ j) {
        tuple<bool, float, float> line;
        if(points[i].x == points[j].x) {
          // for vertical line
          auto &tmp = hash_lines[make_tuple(0, 0, points[i].x)];
          auto p = find(tmp.begin(), tmp.end(), i);
          if (p == tmp.end()) {
            tmp.emplace_back(i);
          }
          p = find(tmp.begin(), tmp.end(), j);
          if (p == tmp.end()) {
            tmp.emplace_back(j);
          }
        }
        else {
          int num = (points[i].y - points[j].y);
          int den = (points[i].x - points[j].x);
          int gcd = GCD(num, den);
          num /= gcd;
          den /= gcd;

          float d = points[i].y - ((float)num / (float)den) * points[i].x;
          list<int> &tmp = hash_lines[make_tuple(num, den, d)];
          auto p = find(tmp.begin(), tmp.end(), i);
          if (p == tmp.end()) {
            tmp.emplace_back(i);
          }
          p = find(tmp.begin(), tmp.end(), j);
          if (p == tmp.end()) {
            tmp.emplace_back(j);
          }
        }
      }
    }

    int max = 0;
    for (auto &hash_line : hash_lines) {
      if (max < hash_line.second.size()) {
        max = hash_line.second.size();
      }
    }
    return max;
  }

  static int GCD(int a, int b) {
    if (b == 0) return a;
    // if b > a, than a % b == a, so this is equivalent to switching but without if statement, brilliant!
    else return GCD(b, a % b);
  }
};
