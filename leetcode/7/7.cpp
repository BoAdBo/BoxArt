class Solution {
public:
  int reverse(int x) {
    // overflow

    bool negative = x < 0;
    std::string str = std::to_string(std::abs(x));

    for (int i = 0; i < (str.size()) >> 1; ++ i)
      std::swap(str[i], str[str.size() - 1 - i]);

    if (negative) {
      str.insert(0, 1, '-');
    }
    long ret = std::atol(str.c_str());
    //if (ret < std::pow(2, 31)-1 && ret > -std::pow(2, 31))
    if (ret < 2147483647 && ret > -2147483648)
      return ret;
    return 0;
  }
};
