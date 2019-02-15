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
  std::unordered_map<unsigned int, std::unordered_set<std::string>> value_keeper;
  /** Initialize your data structure here. */
  AllOne() { }

  /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
  void inc(string key) {
    unsigned int value = ++keeper[key];
    if (value > 1) {
      value_keeper[value-1].erase(key);
      value_keeper[value].insert(key);
    } else {
      value_keeper[value].insert(key);
    }
  }

  /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
  void dec(string key) {
    unsigned int value = --keeper[key];
    if (value >= 1) {
      value_keeper[value+1].erase(key);
      value_keeper[value].insert(key);
    } else {
      value_keeper[value+1].erase(key);
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
