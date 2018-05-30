#include <climits>

class Solution {
public:
  int thirdMax(std::vector<int>& nums) {
    long int max = LONG_MIN;
    long int second_max = LONG_MIN;
    long int third_max = LONG_MIN;

    for ( const auto &num : nums ) {
      if ( num >= max ) {
        if ( num == max ) { continue; }
        third_max = second_max;
        second_max = max;
        max = num;

      }
      else if ( num >= second_max ){
        if ( num == second_max ) { continue; }
        third_max = second_max;
        second_max = num;
      }
      else if ( num >= third_max ) {
        if ( num == third_max ) { continue; }
        third_max = num;
      }
    }

    if ( third_max == LONG_MIN ) {
      return (int)max;
    }
    else {
      return (int)third_max;
    }
  }
};
