class Solution {
private:
  std::string singleDigit(const std::string& num, char n) {
    int carry = 0;
    std::string result = "";
    for (auto iter = num.rbegin(); iter != num.rend(); ++ iter) {
      int multiply = (*iter - '0') * (n - '0') + carry;
      int remain = multiply % 10;
      carry = multiply / 10;
      result.push_back(remain + '0');
    }
    if (carry > 0) result.push_back(carry + '0');
    std::reverse(result.begin(), result.end());
    return result;
  }

  std::string addition(const std::string& num1, const std::string& num2) {
    std::string result = "";
    auto iter1 = num1.crbegin();
    auto iter2 = num2.crbegin();
    int carry = 0;
    while (iter1 != num1.crend() && iter2 != num2.crend()) {
      int sum = (*iter1 - '0') + (*iter2 - '0') + carry;
      int remain = sum % 10;
      carry = sum / 10;
      result.push_back(remain + '0');
      ++iter1; ++iter2;
    }

    while (iter1 != num1.crend()) {
      int sum = (*iter1 - '0') + carry;
      int remain = sum % 10;
      carry = sum / 10;
      result.push_back(remain + '0');
      ++iter1;
    }

    while (iter2 != num2.crend()) {
      int sum = (*iter2 - '0') + carry;
      int remain = sum % 10;
      carry = sum / 10;
      result.push_back(remain + '0');
      ++iter2;
    }

    if (carry > 0) result.push_back(carry + '0');
    std::reverse(result.begin(), result.end());
    return result;
  }
public:
  string multiply(string num1, string num2) {
    std::string result = "";
    if (num2 == "0" || num1 == "0") return "0";
    for (char n : num2) {
       auto multiply = singleDigit(num1, n);
       result = addition(result, multiply);
       result.push_back('0');
    }
    result.pop_back();
    return result;
  }
};
