#include "predefined.cpp"

class Solution {
public:
  bool isMatch(string s, string p) {
    return match(s.cbegin(), s.cend(), p.cbegin(), p.cend());
  }

  // passed on 2019.2.15
  template <typename Iterator>
  bool match(Iterator first1, Iterator last1,
             Iterator first2, Iterator last2) {
    if (first2 == last2) return first1 == last1;
    Iterator matched;
    Iterator star = last2;

    while (first1 != last1) {
      if (first2 != last2) {
        if (*first1 == *first2 || *first2 == '?') { ++first1; ++first2; continue; }
        else if (*first2 == '*') { star = first2; matched = first1; ++first2; continue; }
      }
      // cannot continue with the match, fall back to the last '*', skip one character
      if (star != last2) { first2 = star+1; first1 = matched+1; ++matched; continue; }
      return false;
    }

    // consume all '*' in the back
    while (first2 != last2 && *first2 == '*') ++first2;
    return first2 == last2;
  }

  // slow recursive version, TLE
  template <typename Iterator>
  bool match(Iterator first1, Iterator last1,
             Iterator first2, Iterator last2) {
    if (first1 == last1 && first2 == last2)
      return true;

    // first1 == last1
    if (first1 == last1) {
      // first1 == last1 && first2 != last2
      if (*first2 == '*') {
        return match(first1, last1, first2+1, last2);
      }
      else return false;
    }

    // first1 != last1 && first2 != last2
    // && *first2 == '*'
    if (first2 != last2) {
      if (*first2 == '*') {
        return match(first1+1, last1, first2, last2) ||
          match(first1, last1, first2+1, last2);
      }
      else {
        if (*first1 == *first2 || *first2 == '?')
          return match(first1+1, last1, first2+1, last2);
      }
    }

    // first1 != last1 && first2 == last2
    return false;
  }
};
