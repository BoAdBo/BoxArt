class Solution {
public:
  vector<string> addOperators(string num, int target) {
    if (num.empty()) return {};
    std::vector<std::string> res;
    helper(num, target, res, "");
    return res;
  }

  void helper(string num, int target, std::vector<std::string> &res, std::string candidate) {
    if (num.empty()) {
      // evalutate the candidates
      long value;
      // try {
      value = evaluate(candidate.cbegin(), candidate.cend());
        //}
      // catch (std::out_of_range) {
      //   return;
      // }
      if (value == target) res.push_back(std::move(candidate));
    }
    else {
      if (num.size() == 1) {
        helper(num.substr(1), target, res, candidate + num.front());
      }
      else {
        // 0 in first of candidate, skip
        if (!(num.front() == '0' &&
             (candidate.empty() ||
              candidate.back() == '+' ||
              candidate.back() == '-' ||
              candidate.back() == '*'))) {
          helper(num.substr(1), target, res, candidate + num.front());
        }
        helper(num.substr(1), target, res, candidate + num.front() + '+');
        helper(num.substr(1), target, res, candidate + num.front() + '-');
        helper(num.substr(1), target, res, candidate + num.front() + '*');
      }
    }
  }

  template <typename Iterator>
  long evaluate(Iterator first, Iterator last) {
    Iterator range1 = first, range2 = first;
    std::vector<long> ints;
    std::vector<char> ops;
    while (true) {
      while (range2 != last &&
             *range2 != '+' &&
             *range2 != '-' &&
             *range2 != '*') {
        ++range2;
      }
      ints.push_back(std::stol(std::string(range1, range2)));
      if (range2 == last) break;
      ops.push_back(*range2);
      // assume no invalid candidate say: "1+"
      // having an op in the back
      ++range2;
      range1 = range2;
    }

    for (auto iter = ops.begin(); iter != ops.end(); ) {
      if (*iter == '*') {
        // offset
        const auto i = std::distance(ops.begin(), iter);
        long new_int = ints[i] * ints[i+1];
        iter = ops.erase(iter);
        *ints.erase(ints.begin() + i) = new_int;
      }
      else {
        ++iter;
      }
    }

    for (auto iter = ops.begin(); iter != ops.end(); ) {
      if (*iter == '+') {
        const auto i = std::distance(ops.begin(), iter);
        long new_int = ints[i] + ints[i+1];
        iter = ops.erase(iter);
        *ints.erase(ints.begin() + i) = new_int;
      }
      else if (*iter == '-') {
        const auto i = std::distance(ops.begin(), iter);
        long new_int = ints[i] - ints[i+1];
        iter = ops.erase(iter);
        *ints.erase(ints.begin() + i) = new_int;
      }
      else {
        ++iter;
      }
    }

    // ints.size() == 1, ops.size() == 0
    assert(ints.size() == 1 && ops.empty());
    return ints.front();
  }
};
