class Solution {
public:
  vector<int> exclusiveTime(int n, vector<string>& logs) {
    std::stack<int> sp;
    std::vector<int> exclusive(n, 0);
    int id, time, currentTime;
    bool startOrNot;
    std::tie(id, time, startOrNot) = parse_log(logs.front());
    currentTime = time;
    sp.push(id);

    for (int i = 1; i < logs.size(); ++ i) {
      std::tie(id, time, startOrNot) = parse_log(logs[i]);
      // start
      if (startOrNot) {
        // before pushing callee, should update caller's exclusive time
        if (!sp.empty()) {
          exclusive[sp.top()] += time - currentTime;
        }
        sp.push(id);
        currentTime = time;
      }
      else {
        exclusive[sp.top()] += time - currentTime + 1;
        sp.pop();
        currentTime = time + 1;
      }
    }
    return exclusive;
  }

  // bool true => start
  std::tuple<int, int, bool> parse_log(const std::string& log) {
    auto first = log.find(':');
    auto second = log.find(':', first+1);
    int id = my_stoi(log.cbegin(), log.cbegin() + first);
    int time = my_stoi(log.cbegin() + second + 1, log.cend());
    return {id, time, log.substr(first+1, second-first-1) == "start"};
  }

  template <typename Iterator, int base = 10>
  int my_stoi(Iterator first, Iterator second) {
    int acc = 0;
    for (; first != second; ++first) {
      acc = acc * base + (*first - '0');
    }
    return acc;
  }
};
