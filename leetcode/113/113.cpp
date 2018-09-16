class Solution {
public:
  vector<vector<int>>
  pathSum(TreeNode* root, int sum) {
    std::vector<std::vector<int>> target;
    std::vector<int> interm;
    if (root == nullptr) return target;
    pathSumRec(root, sum, target, interm);
    return target;
  }

  // this function takes nullptr root
  void pathSumRec(TreeNode *root, int sum,
                  vector<vector<int>> &target,
                  std::vector<int> &prePath,
                  int position = 0,
                  int acc = 0)
  {
    // if at leaf and sum matches up
    if (root->left == nullptr && root->right == nullptr && acc + root->val == sum) {

      if (position >= prePath.size()) prePath.emplace_back(root->val);
      else prePath[position] = root->val;

      std::vector<int> appended(position+1);
      std::copy(&prePath[0], &prePath[position+1], appended.begin());

      target.emplace_back(std::move(appended));
    }
    else {
      if (position >= prePath.size()) prePath.emplace_back(root->val);
      else prePath[position] = root->val;
      acc = acc + root->val;
      if (root->left != nullptr) {
        pathSumRec(root->left, sum, target, prePath, position+1, acc);
      }
      if (root->right != nullptr) {
        pathSumRec(root->right, sum, target, prePath, position+1, acc);
      }
    }
  }
};
