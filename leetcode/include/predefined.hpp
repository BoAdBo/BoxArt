#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <ratio>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};
