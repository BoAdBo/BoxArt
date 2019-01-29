/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  // assume that original root tree contains p and q
  // assume that p and q are unique within root
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // auto res = LCA(root, p, q);
    // assert(res.second);
    // return res.first;
    if (!root) return nullptr;
    // if we find root as p or q, then
    // case1: another is in the subtree of root
    // case2: otherwise
    if (root == p || root == q) return root;
    auto left = lowestCommonAncestor(root->left, p, q);
    auto right = lowestCommonAncestor(root->right, p, q);
    // both not nullptr -> common ancestor
    // left and right cannot both be ca, so one p, one q
    if (left && right) return root;
    // considering the upper case1, case2.
    // case1 of left: left is the lca, propagate up
    // case2 of left: we found left as p or q, propagate up
    // right likewise
    // in summary, we return the nonempty one or nullptr
    return (left != nullptr ? left : right);
  }

  std::pair<TreeNode*, bool> LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return std::make_pair(nullptr, false);
    TreeNode* left;
    TreeNode* right;
    bool foundLeft, foundRight;
    std::tie(left, foundLeft) = LCA(root->left, p, q);
    std::tie(right, foundRight) = LCA(root->right, p, q);
    if (foundLeft) return std::make_pair(left, true);
    if (foundRight) return std::make_pair(right, true);

    // if (root == p || root == q) {
    //   // found both, return root as lca
    //   if (left == p || left == q || right == p || right == q)
    //     return std::make_pair(root, true);
    //   // just found one
    //   else
    //     return std::make_pair(root, false);
    // }
    if (root == p) {
      // found both, return root as lca
      if (left == q || right == q) return std::make_pair(root, true);
      // just found one
      else return std::make_pair(root, false);
    }
    else if (root == q) {
      if (left == p || right == p) return std::make_pair(root, true);
      else return std::make_pair(root, false);
    }
    else {
      // not found lca, then if left and right are not nullptr
      // we have p and q
      if (left && right)
        return std::make_pair(root, true);

      // else return left, right if they are not nullptr
      if (left) return {left, false};
      if (right) return {right, false};

      // nothing found, just return nullptr
      return {nullptr, false};
    }
  }

  TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    if (root == p || root == q) return root;
    auto left = lca(root->left, p, q);
    auto right = lca(root->right, p, q);
    // p && q from predecessors
    // because impossible for left && right subtree finding the ca
    // the same time
    if (left && right) return root;
    return (left != nullptr ? left : right);
    // if (left) return left;
    // if (right) return right;
    // return nullptr;
  }
};
