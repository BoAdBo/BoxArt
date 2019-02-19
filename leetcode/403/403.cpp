// fastest solution yet, suspect it's not fast for common case. But for the OJ, it's fast
class Solution {
public:
  bool canCross(vector<int>& stones) {
    if (stones.empty()) return false;
    if (stones.size() == 1) return true;
    if (stones[1] != 1) return false;
    if (stones.size() == 2) return true;

    unordered_set<int> posi_set;
    for (int i = 0; i < stones.size(); i++) {
      if (i > 0 && stones[i] - stones[i-1] > i) return false;
      posi_set.insert(stones[i]);
    }

    return dfs(posi_set, stones[1], 1, stones.back());
  }

private:
  bool dfs(unordered_set<int>& posi_set, int posi, int vel, int target) {
    if (posi+vel == target || posi+vel+1 == target || posi+vel-1 == target) return true;

    for (int v = vel+1; v >= vel-1; v--) {
      if (v == 0) continue;
      if (posi_set.count(posi+v) && dfs(posi_set, posi+v, v, target)) return true;
    }
    return false;
  }
};

// slower or concise version of mine
class Solution {
public:
  // slower
  bool canCross(vector<int> &stones) {
    std::unordered_map<int, std::unordered_set<int>> prev = {{0, {0}}};
    const int &target = stones.back();
    for (int pos : stones) {
      for (auto it = prev[pos].cbegin(); it != prev[pos].cend(); ++it) {
        if (*it > 1) { prev[pos + *it - 1].insert(*it-1); }
        prev[pos + *it].insert(*it);
        prev[pos + *it + 1].insert(*it+1);
      }
    }
    return prev[target].size();
  }
};

// mine
class Solution {
public:
  // stones.size() >= 2,
  // The first stone is at 0, the second stone must be at 1,
  // Since first jump must be 1 unit
  bool canCross(vector<int>& stones) {
    for (int i = 1; i < stones.size(); ++ i) {
      if (stones[i] - stones[i-1] > i) return false;
    }
    std::unordered_map<int, std::vector<int>> prev;
    int target = stones.back();
    const std::unordered_set<int> haveStones(stones.cbegin(), stones.cend());
    std::unordered_set<int> filter;
    prev[1].push_back(1);
    for (int i = 1; i < stones.size(); ++ i) {
      const int pos = stones[i];
      if (prev.find(pos) == prev.end())
        continue;

      // Have a filter to filter out from pos to k.
      // There are prev steps that enable frog to jump from pos to k
      // Therefore it could add multiple same distances to prev[k]
      filter.clear();
      for (int p : prev[pos]) {
        // three options, p-1, p, p+1
        const int step1 = p-1;
        const int step2 = p;
        const int step3 = p+1;
        if (pos + step1 >= step1 &&
            haveStones.find(pos + step1) != haveStones.end() &&
            step1 > 0 &&
            filter.find(pos + step1) == filter.end()) {
          filter.insert(pos + step1);
          prev[pos + step1].push_back(step1);
        }
        if (pos + step2 >= step2 &&
            haveStones.find(pos + step2) != haveStones.end() &&
            filter.find(pos + step2) == filter.end()) {
          filter.insert(pos + step2);
          prev[pos + step2].push_back(step2);
        }
        if (pos + step3 >= step3 &&
            haveStones.find(pos + step3) != haveStones.end() &&
            filter.find(pos + step3) == filter.end()) {
          filter.insert(pos + step3);
          prev[pos + step3].push_back(step3);
        }
      }
      if (prev.count(target) > 0) return true;
    }
    return false;
  }
};
