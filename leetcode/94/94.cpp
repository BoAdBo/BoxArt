class SolutionIter {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    std::stack<TreeNode *> nodeStack;
    std::vector<int> target;

    while (root != nullptr) {
      while (root != nullptr) {
        nodeStack.push(root);
        root = root->left;
      }

      // find the first right sub-tree in the stack
      // And maintain the invariant(by poping and pushing)
      while (root == nullptr && !nodeStack.empty()) {
        root = nodeStack.top();
        nodeStack.pop();
        target.emplace_back(root->val);
        root = root->right;
      }

      // if no node is found, end iteration
      // if found, begin searching in left tree first
      // maintaining the invariant with stack
    }
    return target;
  }
};

class SolutionRecur {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> results;
    inorderTraversalRecur(root, results);
    return results;
  }

  void inorderTraversalRecur(TreeNode *root, vector<int> &results) {
    if (root != nullptr) {
      inorderTraversalRecur(root->left, results);
      results.emplace_back(root->val);
      inorderTraversalRecur(root->right, results);
    }
  }
};

class Solution : public SolutionIter {

};
