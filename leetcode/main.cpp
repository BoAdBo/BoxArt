#include "149/149.cpp"
int main() {
  vector<Point> test;
  test.emplace_back(1,1);
  test.emplace_back(1,2);
  test.emplace_back(2,1);
  //test.emplace_back(3,10);
  //test.emplace_back(3,10);
  //test.emplace_back(0,2);
  //test.emplace_back(0,2);
  //cout << Solution::GCD(8,4) << endl;

  //Point x(1, 1);
  //Point y(1, 2);

  Solution testing;
  cout << testing.maxPoints(test) << endl;
}
