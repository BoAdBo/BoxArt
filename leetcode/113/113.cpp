class Solution {
public:
  vector<vector<int>>
  pathSum(TreeNode* root, int sum) {
    std::vector<std::vector<int>> target;
    if (root == nullptr) return target;
    pathSumRec(root, sum, target);
    return target;
  }

  // this function takes nullptr root
  void pathSumRec(TreeNode *root, int sum,
                  vector<vector<int>> &target,
                  std::vector<int> prePath = std::vector<int>(),
                  int acc = 0)
  {
    // if at leaf and sum matches up
    if (root->left == nullptr && root->right == nullptr && acc + root->val == sum) {
      prePath.emplace_back(root->val);
      target.emplace_back(std::move(prePath));
    }
    else {
      prePath.emplace_back(root->val);
      acc = acc + root->val;
      if (root->left != nullptr) {
        pathSumRec(root->left, sum, target, prePath, acc);
      }
      if (root->right != nullptr) {
        pathSumRec(root->right, sum, target, prePath, acc);
      }
    }
  }
};
