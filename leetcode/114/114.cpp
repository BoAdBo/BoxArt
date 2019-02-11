class Solution {
public:
  void flatten(TreeNode* root) {
    if (root)
      helper1(root);
  }

  TreeNode* helper(TreeNode* root) {
    if (!root) return nullptr;
    // if (!root->left) return helper(root->left);
    auto lastLeft = helper(root->left);
    auto lastRight = helper(root->right);

    // lastLeft and lastRight could be nullptr
    // if left sub tree empty, root doesn't change
    if (lastLeft) {
      lastLeft->right = root->right;
      root->right = root->left;
      root->left = nullptr;
    }

    // return the last visited node of the sub tree
    if (lastRight) return lastRight;
    else if (lastLeft) return lastLeft;
    else return root;
    // return (lastRight != nullptr ? lastRight : lastLeft);
  }

  TreeNode* helper1(TreeNode* root) {
    bool l = (root->left == nullptr);
    bool r = (root->right == nullptr);
    if (l && r) {
      return root;
    }
    // if left sub tree is empty, just proceed
    if (r) {
      root->right = root->left;
      root->left = nullptr;
      return helper1(root->right);
    }
    if (l)
      return helper1(root->right);
    else {
      auto left = helper1(root->left);
      auto right = helper1(root->right);
      std::cout << root->val << ' ' << root->left->val << ' ' << root->right->val << '\n';

      left->right = root->right;
      root->right = root->left;
      root->left == nullptr;

      return right;
    }
  }
};
