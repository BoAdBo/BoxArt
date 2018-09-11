// class Solution {
// public:
//   /*
//    * Naive way, find the highest of the two side, h1, h2, keep it as hold = min(h1, h2)
//    * An array to hold this, and accumulate in the end, hold - self on each node
//    * self stands for its own height
//    */
//   int trap(vector<int>& height) {
//     std::vector<int> holderHeight;
//     holderHeight.reserve(height.size());

//     for (auto i = height.begin(); i != height.end(); ++ i) {
//       // go left
//       int leftMax = 0, rightMax = 0;
//       std::for_each(height.begin(), i,
//                     [&leftMax](int a) {
//                       if (leftMax < a) leftMax = a;
//                     });
//       // go right
//       std::for_each(i, height.end(),
//                     [&rightMax](int a) {
//                       if (rightMax < a) rightMax = a;
//                     });

//       holderHeight.emplace_back(std::min(leftMax, rightMax));
//     }

//     assert(holderHeight.size() == height.size() &&
//            "They should have the same size");

//     int water = 0;
//     for (auto i = 0ul; i < height.size(); ++ i) {
//       if (holderHeight[i] > height[i]) {
//         water += (holderHeight[i] - height[i]);
//       }
//     }

//     return water;
//   }
// };
class Solution {
public:
  int trap(vector<int>& height) {
    if (height.size() == 0) { return 0; }
    std::vector<int> left, right;
    left.reserve(height.size());
    right.reserve(height.size());

    left.emplace_back(0);
    for (auto i = 1ul; i < height.size(); ++ i)
      left.emplace_back(std::max(left[i-1], height[i-1]));

    // right is backwards, meaning index 0 points to the last one
    right.emplace_back(0);
    for (auto i = 1ul; i < height.size(); ++ i)
      right.emplace_back(std::max(right[i-1], height[height.size() - i]));

    assert(left.size() == right.size() && right.size() == height.size());

    int water = 0;
    for (auto i = 0ul; i < height.size(); ++ i) {
      auto min = std::min(left[i], right[height.size() - i]);
      if (min > height[i])
        water += (min - height[i]);
    }
    return water;
  }
};
