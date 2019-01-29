
#ifndef _NEWJOY_PREDEFINED_HPP_
#define _NEWJOY_PREDEFINED_HPP_

#include <vector>
#include <iterator>
#include <map>
#include <list>
#include <stack>
#include <iostream>
#include <ratio>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <queue>

using namespace std;

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

#endif /* _NEWJOY_PREDEFINED_HPP_ */
