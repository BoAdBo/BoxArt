static const auto io_sync_off = []()
                                {
                                  std::ios::sync_with_stdio(false);
                                  std::cin.tie(nullptr);
                                  std::cout.tie(nullptr);
                                  return nullptr;
                                }();

class Solution {
public:
  int divide(int dividend_int, int divisor_int) {
    int quotient = 0;
    // the only possible overflow
    long dividend = dividend_int;
    long divisor = divisor_int;
    if (dividend == std::numeric_limits<int>::min() &&
        divisor == -1) {
      return std::numeric_limits<int>::max();
    }
    bool signedMask = true;
    if (dividend < 0) {
      dividend = -dividend;
      signedMask = !signedMask;
    }
    if (divisor < 0) {
      divisor = -divisor;
      signedMask = !signedMask;
    }

    long div = divisor;
    int addOn = 1;

    while (dividend >= divisor) {
      dividend -= div;
      div += div;
      quotient += addOn;
      addOn += addOn;
      if (dividend < div) {
        div = divisor;
        addOn = 1;
      }
    }

    // signedMask true => they have the same signed.
    if (!signedMask) {
      quotient = -quotient;
    }
    return quotient;
  }
};
