#include <vector>
#include <map>
#include <list>
#include <stack>
#include <iostream>
#include <ratio>
#include <algorithm>
#include <cmath>
#include <cassert>

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
