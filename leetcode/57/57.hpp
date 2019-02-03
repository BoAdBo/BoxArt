#include "predefined.hpp"

class Solution {
public:
  // bool overlapped(Interval a, Interval b) {
  //   return (a.start < b.end) || (a.end < b.start);
  // }

  Interval mergeInterval(Interval a, Interval b) {
    return Interval(std::min(a.start, b.start), std::max(a.end, b.end));
  }

  // class Solution {
  // public:
  //   vector<Interval> insert(vector<Interval>& intervals, const Interval& newInterval) {
  //     auto range = equal_range(intervals.begin(), intervals.end(), newInterval,
  //                              [](const Interval &intv1, const Interval &intv2) { return intv1.end < intv2.start; });
  //     auto itl = range.first, itr = range.second;
  //     if(itl == itr)intervals.insert(itl, newInterval);
  //     else {
  //       --itr;
  //       itr->start = min(newInterval.start, itl->start);
  //       itr->end = max(newInterval.end, itr->end);
  //       intervals.erase(itl, itr);
  //     }
  //     return intervals;
  //   }
  // };

  vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    auto range = std::equal_range(intervals.begin(), intervals.end(), newInterval,
                                  [](const Interval &intv1, const Interval &intv2) {
                                    return intv1.end < intv2.start;
                                  });
    auto itl = range.first, itr = range.second;
    if (itl == itr) { intervals.insert(itr, newInterval); }
    else {
      itr--;
      itr->start = std::min(newInterval.start, itl->start);
      itr->end = std::max(newInterval.end, itr->end);
      intervals.erase(itl, itr);
    }
    return std::vector<Interval>(intervals);
  }

  // vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
  //   auto iter = intervals.begin();
  //   std::vector<Interval> results;
  //   // find first overlapped
  //   while (iter != intervals.end() &&
  //          iter->end < newInterval.start) {
  //     ++iter;
  //   }
  //   auto begin = iter;
  //   // find last overlapped's next
  //   while (iter != intervals.end() &&
  //          iter->start <= newInterval.end) {
  //     ++iter;
  //   }
  //   auto end = iter;

  //   if (begin == end) {
  //     intervals.insert(end, newInterval);
  //     return std::vector<Interval>(intervals.cbegin(), intervals.cend());
  //   }

  //   else {
  //     iter = begin;
  //     while (iter != end) {
  //       newInterval = mergeInterval(*iter, newInterval);
  //       ++iter;
  //     }
  //   }

  //   for (iter = intervals.begin(); iter != begin; ++iter) {
  //     results.push_back(*iter);
  //   }
  //   results.push_back(newInterval);
  //   for (iter = end; iter != intervals.end(); ++ iter) {
  //     results.push_back(*iter);
  //   }
  //   return results;
  // }
};
