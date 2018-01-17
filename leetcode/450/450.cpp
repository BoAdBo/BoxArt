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
  TreeNode *p;
public:
  TreeNode* find_min_right(TreeNode *root) {
    if(root->left) {
      p = root;
      return find_min_right(root->left);
    }
    else {
      return root;
    }
  }

  TreeNode* deleteNode(TreeNode* root, int key) {
    if(root) {
      if(root->val == key) {
        if(!root->left && !root->right) {
          return NULL;
        }
        else if(!root->left) {
          return root->right;
        }
        else if(!root->right) {
          return root->left;
        }
        else {
          // find the min of right, and replace it with root
          p = root->right;
          TreeNode *min = find_min_right(root->right);
          p->left = (min->right ? min->right : NULL);
          min->right = root->right;
          min->left = root->left;
          return min;
        }
      }
      else if(root->val < key) {
        root->left = deleteNode(root->left, key);
        return root;
      }
      else {
        root->right = deleteNode(root->right, key);
        return root;
      }
    }
    else {
      return root;
    }
  }
};
