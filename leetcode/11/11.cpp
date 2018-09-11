class Solution {
public:

  /*
   * find two lines l1,l2 and let y = min(l1, l2), x = dist(l1, l2)
   * such that argmax(x * y)
   */
  // int maxArea(vector<int>& height) {
  //   int max = 0;

  //   for (auto i = 0ul; i < height.size(); ++ i) {

  //     for (auto j = i+1; j < height.size(); ++ j) {
  //       auto y = std::min(height[i], height[j]);
  //       auto x = j - i;

  //       auto area = x * y;
  //       max = (max >= area ? max : area);
  //     }

  //   }

  //   return max;
  // }

  /*
   * Start from the widest, and cut the nodes that doesn't have a high height,
   * Since it's impossible for them to have a higher area than the wider outside
   * nodes.
   * And due to the height is determined by the lower, if the node on one side
   * is lower than lower node of the outside. Hence the two while each iterates
   * on one side
   */
  int maxArea(vector<int>& height) {
    int waterMax = 0;
    int i = 0, j = height.size()-1;

    int h;
    while (i < j) {
      h = std::min(height[i], height[j]);
      waterMax = std::max(waterMax, (j - i) * h);
      while (h >= height[i] && i < j) ++i;
      while (h >= height[j] && i < j) --j;
    }

    return waterMax;
  }
};
