class Solution {
public:
  bool isMatch(string s, string p) {
    return isMatch(std::begin(s), std::end(s), std::begin(p), std::end(p), '!');
  }

  // template <typename Iterator>
  // bool isMatch(Iterator first1, Iterator last1,
  //              Iterator first2, Iterator last2,
  //              char previous) {
  //   if (first1 == last1 && first2 == last2) return true;
  //   // pattern exhausted
  //   if (first2 == last2) return false;
  //   // text exhausted, two cases needed to explore
  //   // handle special cases where "" match "a*"
  //   if (first1 == last1) {

  //     // advance, assume no invalid regular expression
  //     // pattern == "*"
  //     if (*first2 == '*')
  //       return isMatch(first1, last1, first2+1, last2, previous);

  //     // the next is '*', advance
  //     if (first2+1 != last2 && *(first2+1) == '*')
  //       return isMatch(first1, last1, first2+2, last2, previous);

  //     // neither of those cases
  //     return false;
  //   }
  //   if (*first1 == *first2 || *first2 == '.')
  //     return isMatch(first1+1, last1, first2+1, last2, *first2);

  //   if (*first2 == '*' && (*first1 == previous || previous == '.'))
  //     return isMatch(first1+1, last1, first2, last2, previous);
  //   return false;
  // }

  template <typename Iterator>
  bool isMatch(Iterator first1, Iterator last1,
               Iterator first2, Iterator last2) {
    if (first1 == last1 && first2 == last2) return true;

    // pattern exhausted first
    if (first2 == last2) return false;
    // match or not
    bool match = first1 != last1 && (*first2 == '.' || *first2 == *first1);

    // look ahead, '*' found
    if (first2+1 != last2 && *(first2+1) == '*') {
      // char + '*', ignore or advance.
      return isMatch(first1, last1, first2+2, last2) ||
        (match && isMatch(first1+1, last1, first2, last2));
    }
    // '*' not found, advance if matched
    else {
      return match && isMatch(first1+1, last1, first2+1, last2);
    }
  }
};
