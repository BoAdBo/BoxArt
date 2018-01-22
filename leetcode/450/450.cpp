/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <stdlib.h>
#include <stdio.h>

#define node(val) new TreeNode(val)

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

  TreeNode *deleteNode(TreeNode *root, int key) {
    if(root) {
      if(key > root->val) {
        root->right = deleteNode(root->right, key);
        return root;
      }
      else if(key < root->val) {
        root->left = deleteNode(root->left, key);
        return root;
      }
      else {
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
          TreeNode *min = find_min_right(root->right);
          min->left = root->left;// change the entire left subtree to the min node, and skip the root node
          return root->right;
        }
      }
    }
    else {
      return NULL;
    }
  }

};


// TreeNode* deleteNode(TreeNode* root, int key) {
//   if(root) {
//     if(root->val == key) {
//       if(!root->left && !root->right) {
//         return NULL;
//       }
//       else if(!root->left) {
//         return root->right;
//       }
//       else if(!root->right) {
//         return root->left;
//       }
//       else {
//         // find the min of right, and replace it with root
//         TreeNode *min = find_min_right(root->right);
//         root->val = min->val;
//         root->right = deleteNode(root->right, min->val);
//         return root;
//       }
//     }
//     else if(root->val < key) {
//       root->right = deleteNode(root->right, key);
//       return root;
//     }
//     else {
//       root->left = deleteNode(root->left, key);
//       return root;
//     }
//   }
//   else {
//     return root;
//   }
// }


int main() {
  TreeNode *root = node(5);
  root->left = node(3);
  root->right = node(6);
  root->left->left = node(2);
  root->left->right = node(4);
  root->right->right = node(7);
  Solution test;
  test.deleteNode(root, 3);
}
