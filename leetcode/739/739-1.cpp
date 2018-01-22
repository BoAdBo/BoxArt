#include <vector>
#include <stdio.h>
#include <limits.h>
#include <stack>
using std::vector;
using std::stack;

/*
  using an array to record the indexes of temperature, since temperature can only range from [30, 100].
  next[T] : i
  This is simply an inverse of temperatures[i] : T
  And iteration from next[T+1] to next[100] and finding its min element would give the nearest warmest temperature
  And finally update the next array with its temperature and index
 */
// class Solution {
// public:
//   vector<int> dailyTemperatures(vector<int>& temperatures) {
//     vector<int> next(101, INT_MAX); // for temperature in [30, 100]
//     vector<int> nearest(temperatures.size());
//     // -1 as not found
//     for(int i = temperatures.size()-1; i >= 0; --i) {
//       int warmer_index = INT_MAX;
//       // Treat INT_MAX as not found
//       for(int j = temperatures[i] + 1; j <= 100; ++ j) {
//         if(warmer_index > next[j]) {
//           warmer_index = next[j];
//         }
//       }
//       // if found
//       if(warmer_index < INT_MAX) {
//         nearest[i] = warmer_index - i;
//       }
//       // not found
//       else {
//         nearest[i] = 0;
//       }
//       // update
//       next[temperatures[i]] = i;
//     }

//     return nearest;
//   }
// };

/*
 using a stack, maintaining stack such that the temperature is in increasing order from top to bottom
 Iterate from the back of temperatures.
*/

class Solution {
public:
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    stack<int> s;
    vector<int> nearest(temperatures.size());

    for(int i = temperatures.size()-1; i >= 0; -- i) {
      while(!s.empty() && temperatures[s.top()] <= temperatures[i]) {
        s.pop();
      }
      nearest[i] = (s.empty() ? 0 : s.top()-i);
      s.push(i);
    }
    return nearest;
  }
};

// int main() {
//   int x[] = {73, 74, 75, 71, 69, 72, 76, 73};
//   vector<int> vec(x, x + sizeof(x)/sizeof(int));

//   Solution test;
//   vector<int> pec = test.dailyTemperatures(vec);

//   for(int i = 0; i < pec.size(); ++ i) {
//     printf("%d ", pec[i]);
//   }
// }
