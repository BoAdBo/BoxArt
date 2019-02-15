/*
 * Image a group of equal maximal string, and the algorithm only keeps track of one maximal value.
 * Then if one decrement one string in the maximal group, one cannot find another maximal value in O(1) time.
 * Therefore we need to keep track of all the same value in the maximal group.
 *
 * So we need a constant time lookup
 */

class AllOne {
public:
  std::unordered_map<std::string, unsigned int> keeper;
  std::string maxString;
  std::string minString;
  /** Initialize your data structure here. */
  AllOne() {
    maxString = "";
    minString = "";
  }

  /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
  void inc(string key) {
    unsigned int value = ++keeper[key];
    if (keeper[maxString] < value)
  }

  /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
  void dec(string key) {
    auto iter = keeper.find();
    if (iter != keeper.end()) {
      if (*iter == 1) {
        keeper.erase(iter);
      }
      else {
        --(*iter);
      }
    }
  }

  /** Returns one of the keys with maximal value. */
  string getMaxKey() {

  }

  /** Returns one of the keys with Minimal value. */
  string getMinKey() {

  }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */
