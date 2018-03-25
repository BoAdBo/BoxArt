#include "215/215.cpp"
int main() {
  Solution testing;
  //vector<int> test = {3,2,1,5,6,4};
  vector<int> test = {2,1};

  cout << testing.findKthLargest(test, 1) << endl;
  for (int i = 0; i < test.size(); ++ i) {
    cout << test[i] << " ";
  }
  cout << endl;
  //vector<string> test = { "aba", "abb", "abc" };

  //cout << testing.longestCommonPrefix(test) << endl;
  // vector<vector<int>> res=testing.generate(20);
  // //vector<vector<int>>& res=testing.generate(1);
  // for ( int i = 0; i < res.size(); ++ i ) {
  //   for ( int j = 0; j < res[i].size(); ++ j ) {
  //     cout << res[i][j] << " ";
  //   }
  //   cout << endl;
  // }
}
