/**
 * Definition for a binary tree node.
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

class Solution {
public:
  TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    TreeNode *root;
    int value;
    if(!t1 && !t2) return NULL;
    if(t1 != NULL && t2 != NULL) {
      value = t1->val + t2->val;
    }
    else if(t1 != NULL) {
      value = t1->val;
    }
    else if(t2 != NULL) {
      value = t2->val;
    }
    root = new TreeNode(value);
    root->left = mergeTrees((t1 ? t1->left : NULL), (t2 ? t2->left : NULL));
    root->right = mergeTrees((t1 ? t1->right : NULL), (t2 ? t2->right : NULL));
    return root;
  }
};
