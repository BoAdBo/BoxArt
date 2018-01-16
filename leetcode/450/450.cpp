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
  TreeNode *p; // parent
public:

  TreeNode* deleteNode(TreeNode* root, int key) {
    p = root;
    return find_delete(root, key);
  }
};
