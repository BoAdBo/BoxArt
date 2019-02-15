class Solution {
public:
  vector<string> addOperators(string num, int target) {
    std::vector<std::string> res;
    std::string ansBuf(num.size()*2, '\0');
    helper(num, ansBuf, target, 0, 0, res, 0, 0);
    return res;
  }

  /*
   * Need mul to do multiplication
   * eval is the previous evaluation, not considering multiplication in the back.
   * therefore we need mul to augument it.
   */
  void helper(const std::string &num,
              std::string &ansBuf,
              int target,
              int start_pos1, //int end_pos,
              int start_pos2,
              std::vector<std::string> &res,
              long eval, long mul)
  {
    if (num.size() == start_pos1) {
      if (target == eval) {
        res.push_back(ansBuf.substr(0, start_pos2));
      }
    }
    else {
      long number = 0;
      for (int i = 0; i < num.size() - start_pos1; ++ i) {
        if (num[start_pos1] == '0' && i > 0) return;
        number = 10*number + (num[start_pos1+i] - '0');

        if (start_pos1 == 0) {
          ansBuf[start_pos2+i] = num[start_pos1+i];
          helper(num, ansBuf, target, start_pos1+1+i, start_pos2+1+i, res, number, number);
        }
        else {
          ansBuf[start_pos2+1+i] = num[start_pos1+i];
          ansBuf[start_pos2] = '+';
          helper(num, ansBuf, target, start_pos1+1+i, start_pos2+2+i, res, eval + number, number);
          ansBuf[start_pos2] = '-';
          helper(num, ansBuf, target, start_pos1+1+i, start_pos2+2+i, res, eval - number, -number);
          // need to take care of passing mul
          ansBuf[start_pos2] = '*';
          helper(num, ansBuf, target, start_pos1+1+i, start_pos2+2+i, res, (eval - mul) + mul * number, mul * number);
        }
      }
    }
  }
};

class Solution {
public:
  vector<string> addOperators(string num, int target) {
    std::vector<std::string> res;
    helper(num, target, res, "", 0, 0);
    return res;
  }

  /*
   * Need mul to do multiplication
   * eval is the previous evaluation, not considering multiplication in the back.
   * therefore we need mul to augument it.
   */
  void helper(std::string num, int target,
              std::vector<std::string> &res,
              std::string candidate, long eval, long mul)
  {
    if (num.empty()) {
      if (target == eval) {
        res.push_back(std::move(candidate));
      }
    }
    else {
      for (int i = 1; i <= num.size(); ++ i) {
        auto number_str = num.substr(0, i);
        // the number doesn't start with 0
        if (number_str.front() == '0' && number_str.size() > 1) return;
        long number = std::stol(number_str);
        if (candidate.empty()) {
          helper(num.substr(i), target, res, number_str, number, number);
        }
        else {
          helper(num.substr(i), target, res, candidate + '+' + number_str, eval + number, number);
          helper(num.substr(i), target, res, candidate + '-' + number_str, eval - number, -number);
          // need to take care of passing mul
          helper(num.substr(i), target, res, candidate + '*' + number_str, (eval - mul) + mul * number, mul * number);
        }
      }
    }
  }
};

// with bug and painfully slow version
// class Solution {
// public:
//   vector<string> addOperators(string num, int target) {
//     if (num.empty()) return {};
//     std::vector<std::string> res;
//     helper(num, target, res, "");
//     return res;
//   }

//   void helper(string num, int target, std::vector<std::string> &res, std::string candidate) {
//     if (num.empty()) {
//       // evalutate the candidates
//       long value;
//       // try {
//       value = evaluate(candidate.cbegin(), candidate.cend());
//         //}
//       // catch (std::out_of_range) {
//       //   return;
//       // }
//       if (value == target) res.push_back(std::move(candidate));
//     }
//     else {
//       if (num.size() == 1) {
//         helper(num.substr(1), target, res, candidate + num.front());
//       }
//       else {
//         // 0 in first of candidate, skip
//         if (!(num.front() == '0' &&
//              (candidate.empty() ||
//               candidate.back() == '+' ||
//               candidate.back() == '-' ||
//               candidate.back() == '*'))) {
//           helper(num.substr(1), target, res, candidate + num.front());
//         }
//         helper(num.substr(1), target, res, candidate + num.front() + '+');
//         helper(num.substr(1), target, res, candidate + num.front() + '-');
//         helper(num.substr(1), target, res, candidate + num.front() + '*');
//       }
//     }
//   }

//   template <typename Iterator>
//   long evaluate(Iterator first, Iterator last) {
//     Iterator range1 = first, range2 = first;
//     std::vector<long> ints;
//     std::vector<char> ops;
//     while (true) {
//       while (range2 != last &&
//              *range2 != '+' &&
//              *range2 != '-' &&
//              *range2 != '*') {
//         ++range2;
//       }
//       ints.push_back(std::stol(std::string(range1, range2)));
//       if (range2 == last) break;
//       ops.push_back(*range2);
//       // assume no invalid candidate say: "1+"
//       // having an op in the back
//       ++range2;
//       range1 = range2;
//     }

//     for (auto iter = ops.begin(); iter != ops.end(); ) {
//       if (*iter == '*') {
//         // offset
//         const auto i = std::distance(ops.begin(), iter);
//         long new_int = ints[i] * ints[i+1];
//         iter = ops.erase(iter);
//         *ints.erase(ints.begin() + i) = new_int;
//       }
//       else {
//         ++iter;
//       }
//     }

//     for (auto iter = ops.begin(); iter != ops.end(); ) {
//       if (*iter == '+') {
//         const auto i = std::distance(ops.begin(), iter);
//         long new_int = ints[i] + ints[i+1];
//         iter = ops.erase(iter);
//         *ints.erase(ints.begin() + i) = new_int;
//       }
//       else if (*iter == '-') {
//         const auto i = std::distance(ops.begin(), iter);
//         long new_int = ints[i] - ints[i+1];
//         iter = ops.erase(iter);
//         *ints.erase(ints.begin() + i) = new_int;
//       }
//       else {
//         ++iter;
//       }
//     }

//     // ints.size() == 1, ops.size() == 0
//     assert(ints.size() == 1 && ops.empty());
//     return ints.front();
//   }
// };
