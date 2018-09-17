class Solution {
public:
  void arrayFromStr(std::array<int, 26> &result, const std::string & str) {
    result.fill(0);
    for (int i = 0; i < str.size(); ++ i)
      ++result[str[i] - 'a'];
  }

  // strs all lower level case
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    std::vector<std::vector<std::string>> results;
    std::map<std::array<int, 26>, std::vector<int>> lookUpTable;
    std::array<int, 26> temp;

    for (int i = 0; i < strs.size(); ++ i) {
      arrayFromStr(temp, strs[i]);
      lookUpTable[temp].emplace_back(i);
    }

    for (auto it = lookUpTable.cbegin(); it != lookUpTable.cend(); ++ it) {
      std::vector<std::string> result;

      for (const auto &item : it->second)
        result.emplace_back(strs[item]);

      results.emplace_back(std::move(result));
    }

    return results;
  }
};
