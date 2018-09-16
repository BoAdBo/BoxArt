class Solution {
public:
  bool hasPathSum(TreeNode* root, int sum) {
    if (root == nullptr) return false;
    return hasPathSumRecur(root, sum);
  }

  bool hasPathSumRecur(TreeNode* root, int sum, int acc = 0) {
    // at the leaf
    if (root->left == nullptr && root->right == nullptr) {
      return sum == acc + root->val;
    }
    else {
      // don't send root with nullptr
      return
        (root->left == nullptr ? false :
         hasPathSumRecur(root->left, sum, acc + root->val))
        ||
        (root->right == nullptr ? false :
         hasPathSumRecur(root->right, sum, acc + root->val));
    }
  }
};
