#include <list>
#include <stdlib.h>
using std::list;
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
#include <stack>
using std::stack;
// using stack for O(h) memory
class BSTIterator {
private:
  stack<TreeNode*> stk;
  void pushAll(TreeNode * root) {
    while(root != NULL) {
      stk.push(root);
      root = root->left;
    }
  }
public:
  BSTIterator(TreeNode *root) {
    pushAll(root);
  }

  /** @return whether we have a next smallest number */
  bool hasNext() {
    return !stk.empty();
  }

  /** @return the next smallest number */
  int next() {
    TreeNode *node = stk.top();
    stk.pop();
    pushAll(node->right);
    return node->val;
  }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
