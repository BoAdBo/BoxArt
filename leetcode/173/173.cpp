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

class BSTIterator {
private:
  list<int> ordered_array;
  list<int>::const_iterator iter;
  void dfs(TreeNode *root) {
    if (root) {
      dfs(root->left);
      ordered_array.push_back(root->val);
      dfs(root->right);
    }
  }
public:
  BSTIterator(TreeNode *root) {
    dfs(root);
    iter = ordered_array.begin();
  }

  /** @return whether we have a next smallest number */
  bool hasNext() {
    return iter != ordered_array.end();
  }

  /** @return the next smallest number */
  int next() {
    return *iter++;
  }

};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
